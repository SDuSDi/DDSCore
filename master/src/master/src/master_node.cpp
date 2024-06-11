// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"

// JSON library
#include <nlohmann/json.hpp>
using json = nlohmann::json; // for convenience

// MQTT files and setup
#include "publisher.cpp"
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
        string	address  = (argc > 1) ? string(argv[1]) : DFLT_SERVER_ADDRESS,
		        clientID = (argc > 2) ? string(argv[2]) : CLIENT_ID;
        
        std::cout << "\nInitializing for server '" << address << "'..." << std::endl;
	    mqtt::async_client client(address, clientID, PERSIST_DIR);

    	callback cb;
	    client.set_callback(cb);

        auto connOpts = mqtt::connect_options_builder()
            .clean_session()
            .will(mqtt::message(TOPIC, LWT_PAYLOAD, strlen(LWT_PAYLOAD), QOS, false))
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
		action_listener listener;
		tmp_msg["id"] = "0";
		tmp_msg["command"] = "takeoff";
		tmp_msg["param1"] = 2.0;
		std::string PAYLOAD = to_string(tmp_msg);
		std::cout << " Message sent: " << PAYLOAD << std::endl;
		mqtt::message_ptr pubmsg = mqtt::make_message(TOPIC, PAYLOAD);
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
		pubmsg = mqtt::make_message(TOPIC, PAYLOAD);
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


};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ROSMaster>(argc, argv));
    rclcpp::shutdown();

    return 0;
}