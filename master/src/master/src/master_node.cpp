// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"

// JSON library
#include <nlohmann/json.hpp>
using json = nlohmann::json; // for convenience

// MQTT files and setup
#include "publisher.cpp"
#include "listener.cpp"
mqtt::async_client *client = NULL;

json tmp_msg = {
	{"id","-1"},
	{"command","none"},
	{"param1",0},
	{"param2",0},
	{"param3",0},
	{"param4",0},
	{"param5",0}
};

class ROSMaster : public rclcpp::Node
{
public:
    ROSMaster(int argc, char **argv) : Node("rosmaster")
    {
		auto timer_callback = [this]() -> void {
			json instant_data = listener::data;
		};
		timer = this -> create_wall_timer(std::chrono::milliseconds(100), timer_callback);
		std::cout << "Strange shit done" << std::endl;

        std::string	address  = (argc > 1) ? std::string(argv[1]) : publisher::DFLT_SERVER_ADDRESS,
		        clientID = (argc > 2) ? std::string(argv[2]) : publisher::CLIENT_ID;
        
        std::cout << "\nInitializing for server '" << address << "'..." << std::endl;
	    mqtt::async_client client(address, clientID, publisher::PERSIST_DIR);

    	publisher::callback cb;
	    client.set_callback(cb);

        auto connOpts = mqtt::connect_options_builder()
            .clean_session()
            .will(mqtt::message(publisher::TOPIC, publisher::LWT_PAYLOAD, strlen(publisher::LWT_PAYLOAD), publisher::QOS, false))
            .finalize();

        std::cout << "Everything OK. Starting..." << std::endl;

        // Connect
		std::cout << "\nConnecting...";
		mqtt::token_ptr conntok = client.connect(connOpts);
		std::cout << " OK" << std::endl << "Waiting for the connection...";
		conntok->wait();
		std::cout << " OK" << std::endl;

		char x;
		std::cout << "Ready to send message. Press any key to continue." << std::endl; std::cin >> x;

		std::cout << "\nSending takeoff message...";
		publisher::action_listener listener;
		tmp_msg["id"] = "0";
		tmp_msg["command"] = "takeoff";
		tmp_msg["param1"] = 2.0;
		std::string PAYLOAD = to_string(tmp_msg);
		std::cout << " Message sent: " << PAYLOAD << std::endl;
		mqtt::message_ptr pubmsg = mqtt::make_message(publisher::TOPIC, PAYLOAD);
		mqtt::delivery_token_ptr pubtok = client.publish(pubmsg, nullptr, listener);
		pubtok->wait();

		std::this_thread::sleep_for(std::chrono::seconds(20));

		std::cout << "\nSending move message...";
		tmp_msg["id"] = "0";
		tmp_msg["command"] = "move";
		tmp_msg["param1"] = 0.0;
		tmp_msg["param2"] = 0.0;
		tmp_msg["param3"] = 47.4;
		tmp_msg["param4"] = 8.54;
		tmp_msg["param5"] = 2.0;
		PAYLOAD = to_string(tmp_msg);
		std::cout << " Message sent: " << PAYLOAD << std::endl;
		pubmsg = mqtt::make_message(publisher::TOPIC, PAYLOAD);
		pubtok = client.publish(pubmsg, nullptr, listener);
		pubtok->wait();

		auto toks = client.get_pending_delivery_tokens();
		if (!toks.empty())
			std::cout << "Error: There are pending delivery tokens!" << std::endl;

		// Disconnect
		std::cout << "\nDisconnecting...";
		client.disconnect()->wait();
		std::cout << " OK" << std::endl;

    }


private:

	rclcpp::TimerBase::SharedPtr timer;

};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ROSMaster>(argc, argv));
    rclcpp::shutdown();

    return 0;
}