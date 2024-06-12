#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"

namespace publisher{

	const std::string DFLT_SERVER_ADDRESS	{"mqtt://localhost:1883" };
	const std::string CLIENT_ID				{"Link MQTT Publisher" };
	const std::string TOPIC                 {"MQTT-Status-Provider"};
	const std::string PERSIST_DIR {"./persist"};
	const char* LWT_PAYLOAD = "Last will and testament.";
	const int  QOS = 1;
	const auto TIMEOUT = std::chrono::seconds(10);

	/////////////////////////////////////////////////////////////////////////////

	/**
	 * A callback class for use with the main MQTT client.
	 */
	class callback : public virtual mqtt::callback
	{
	public:
		void connection_lost(const std::string& cause) override {
			std::cout << "\nConnection lost" << std::endl;
			if (!cause.empty())
				std::cout << "\tcause: " << cause << std::endl;
		}

		void delivery_complete(mqtt::delivery_token_ptr tok) override {
			std::cout << "\tDelivery complete for token: "
				<< (tok ? tok->get_message_id() : -1) << std::endl;
		}
	};

	/////////////////////////////////////////////////////////////////////////////

	/**
	 * A base action listener.
	 */
	class action_listener : public virtual mqtt::iaction_listener
	{
	protected:
		void on_failure(const mqtt::token& tok) override {
			std::cout << "\tListener failure for token: "
				<< tok.get_message_id() << std::endl;
		}

		void on_success(const mqtt::token& tok) override {
			std::cout << "\tListener success for token: "
				<< tok.get_message_id() << std::endl;
		}
	};

	/////////////////////////////////////////////////////////////////////////////

	/**
	 * A derived action listener for publish events.
	 */
	class delivery_action_listener : public action_listener
	{
		std::atomic<bool> done_;

		void on_failure(const mqtt::token& tok) override {
			action_listener::on_failure(tok);
			done_ = true;
		}

		void on_success(const mqtt::token& tok) override {
			action_listener::on_success(tok);
			done_ = true;
		}

	public:
		delivery_action_listener() : done_(false) {}
		bool is_done() const { return done_; }
	};
	
}