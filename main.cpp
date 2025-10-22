#include "crow_all.h"
#include "db.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    crow::SimpleApp app;
    Database db;

    if (!db.connect("localhost", "root", "your_password", "foodapp")) {
        std::cerr << "Failed to connect to DB. Exiting.\n";
        return 1;
    }

    // Root route
    CROW_ROUTE(app, "/")([](){
        return "🍽️ Food Order API Server Running!";
    });

    // POST /order
    CROW_ROUTE(app, "/order").methods("POST"_method)
    ([&db](const crow::request& req){
        auto body = json::parse(req.body);
        std::string user = body["user"];
        std::string item = body["item"];
        int qty = body["quantity"];

        if (db.insertOrder(user, item, qty)) {
            return crow::response(200, "Order received for " + item);
        } else {
            return crow::response(500, "Database insert failed");
        }
    });

    // WebSocket: /ws
    CROW_ROUTE(app, "/ws")
    .websocket()
    .onopen([](crow::websocket::connection& conn){
        std::cout << "Client connected via WebSocket.\n";
        conn.send_text("Connected to live order updates!");
    })
    .onmessage([](crow::websocket::connection& conn, const std::string& data, bool){
        std::cout << "Message received: " << data << std::endl;
        conn.send_text("Server echo: " + data);
    });

    app.port(8080).multithreaded().run();
}
