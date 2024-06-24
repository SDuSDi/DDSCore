// Base C++ libraries and dependencies
#include <fstream>

// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"

// JSON library
#include <nlohmann/json.hpp>
using json = nlohmann::json; // for convenience

// MQTT files and setup
#include "mqtt.cpp"
mqtt::async_client *client = NULL;

json LoadJsonFile(const char*filename) {
	std::ifstream ifs (filename, std::ifstream::in);
	if (!ifs.is_open()){
		std::cerr << "FATAL ERROR: Could not open file '" << filename << "'" << std::endl;
		exit(1);
	}

	std::string content;
	ifs.seekg(0, std::ios::end);
	content.resize(ifs.tellg());
	ifs.seekg(0, std::ios::beg);
	ifs.read(&content[0], content.size());
	ifs.close();

	json tmp = json::parse(content);
	return tmp;
}

class ROSMaster : public rclcpp::Node
{
public:
    ROSMaster() : Node("rosmaster")
    {
		json commands = LoadJsonFile("/root/master/src/master/src/trajectories.json");

		char x;
		std::cout << "Ready to send message. Press any key to continue." << std::endl; std::cin >> x;

		mqttmaster::action_listener listener("Message Sender");
		std::string PAYLOAD;
		mqtt::message_ptr pubmsg;
		mqtt::delivery_token_ptr pubtok;

		for(int i = 0; i < commands.size(); i++){
			this -> tmp_msg["id"] = std::to_string(i);
			this -> tmp_msg["command"] = "takeoff";
			this -> tmp_msg["param1"] = 2.0;
			PAYLOAD = to_string(this -> tmp_msg);
			pubmsg = mqtt::make_message(mqttmaster::TOPIC_PUB, PAYLOAD);
			pubtok = client->publish(pubmsg, nullptr, listener);
			pubtok->wait();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		while(mqttmaster::data["recipient"]=="-1" && mqttmaster::data["arming_state"]==1 && mqttmaster::data["nav_state"]==4){}
		rclcpp::sleep_for(std::chrono::seconds(int(tmp_msg["param1"])*5));

		for(int j = 0; j < commands.size(); j++){
			this -> tmp_msg["id"] = std::to_string(j);
			this -> tmp_msg["command"] = "move";
			this -> tmp_msg["param1"] = 0.0;
			this -> tmp_msg["param2"] = 0.0;
			this -> tmp_msg["param3"] = commands[std::to_string(j)]["lat"];
			this -> tmp_msg["param4"] = commands[std::to_string(j)]["lon"];
			this -> tmp_msg["param5"] = 2.0;
			PAYLOAD = to_string(this -> tmp_msg);
			pubmsg = mqtt::make_message(mqttmaster::TOPIC_PUB, PAYLOAD);
			pubtok = client->publish(pubmsg, nullptr, listener);
			pubtok->wait();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		auto toks = client->get_pending_delivery_tokens();
		if (!toks.empty())
			std::cout << "Error: There are pending delivery tokens!" << std::endl;

		// Disconnect
		std::cout << "\nDisconnecting...";
		client->disconnect()->wait();
		std::cout << " OK" << std::endl;
		exit(0);
    }

private:

	rclcpp::TimerBase::SharedPtr timer;
	json tmp_msg = {
		{"id","-1"},
		{"command","none"},
		{"param1",0},
		{"param2",0},
		{"param3",0},
		{"param4",0},
		{"param5",0}
	};

};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);

	std::string	address  = (argc > 1) ? std::string(argv[1]) : mqttmaster::SERVER_ADDRESS,
				clientID = (argc > 2) ? std::string(argv[2]) : mqttmaster::CLIENT_ID;
	
	std::cout << "\nInitializing for server '" << address << "'..." << std::endl;
    client = new mqtt::async_client (address, clientID, 0, mqttmaster::PERSIST_DIR); //(const string &serverURI, const string &clientId, int maxBufferedMessages, const string &persistDir)

	auto connOpts = mqtt::connect_options_builder()
		.clean_session()
		.will(mqtt::message(mqttmaster::TOPIC_PUB, mqttmaster::LWT_PAYLOAD, strlen(mqttmaster::LWT_PAYLOAD), mqttmaster::QOS, false))
		.finalize();

    std::cout << "\nInitializing setup...";
    mqttmaster::callback mqtt_cb(*client, connOpts);
    client->set_callback(mqtt_cb);
    std::cout << " OK" << std::endl;
    client->start_consuming();

	std::cout << "\nConnecting...";
	mqtt::token_ptr conntok = client->connect(connOpts);
	std::cout << " OK" << std::endl;
	conntok->wait();
	std::cout << "Waiting for the connection... OK" << std::endl;

	std::cout << "Everything OK. Starting..." << std::endl;

    rclcpp::spin(std::make_shared<ROSMaster>());
    rclcpp::shutdown();

    return 0;
}