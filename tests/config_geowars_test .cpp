#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "geowars/config_components.hpp"
#include "geowars/config.hpp"

using namespace GWars;

TEST_CASE( "Initialize config", "[config]" ) {

    nlohmann::json temp_json_window = {
                                        {"window_specs",
                                            {"width", 1280},
                                            {"height", 720},
                                            {"frame_rate", 60},
                                            {"fullscreen", false}
                                        }
                                      };

    WindowConfig get_window_specs(const nlohmann::json& window_specs)
    {
        WindowConfig temp_window;

        auto w = window_specs.key();
        temp_window.width = w["width"];
        temp_window.height = w["height"];
        temp_window.frame_rate = w["frame_rate"];
        temp_window.fullscreen_mode = w["fullscreen"];

        return temp_window;
    }

    WindowConfig complete_window = get_window_specs(temp_json_window);

    REQUIRE(complete_window.width == 1280 );

}