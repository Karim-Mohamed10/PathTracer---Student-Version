#include <pathtracer.hpp>
#include <scene_setup.hpp>

#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>

std::string str_to_lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](char c) { return std::tolower(c); });
    return str;
}

int main(int argc, char** argv) {
    // Default Configuration (Change them during development to help with debugging)
    std::string scene_name = "cornel-box";
    std::string output_path = "";
    uint32_t sample_count = 1000, max_bounces = 5;
    bool no_bvh = false;
    std::string debug_mode = "none";

    // Read the configuration from the commandline arguments.
    if(argc > 1) {
        std::string argument = str_to_lower(std::string(argv[1]));
        if(argument == "--help" || argument == "-h") {
            printf("usage: pathtracer scene-name [options]\n");
            printf("\n");
            printf("positional arguments:\n");
            printf("  scene-name            the name of the scene to render (default: %s)\n", scene_name.c_str());
            printf("\n");
            printf("optional arguments:\n");
            printf("  --output-path, -o     the output path of the rendered image (default: scene-name followed by .png)\n");
            printf("  --samples, -s         the number of samples per pixel (default: %u)\n", sample_count);
            printf("  --bounces, -b         the maximum number of bounces per ray (default: %u)\n", max_bounces);
            printf("  --no-bvh, -n          disable the use of a bounding volume hierarchy (default: %s)\n", no_bvh ? "true" : "false");
            printf("  --debug-mode, -d      the debug mode to use (default: %s)\n", debug_mode.c_str());
            printf("                        valid debug modes are:\n");
            printf("                        - distance\n");
            printf("                        - normal\n");
            return 0;
        }
        scene_name = argument;
        output_path = scene_name + ".png";
        for(int i = 2; i < argc; i++) {
            std::string argument = str_to_lower(std::string(argv[i]));
            if(i + 1 < argc) {
                if(argument == "--samples" || argument == "-s") {
                    int value = std::atoi(argv[i + 1]);
                    if(value != 0) sample_count = value;
                } else if(argument == "--bounces" || argument == "-b") {
                    int value = std::atoi(argv[i + 1]);
                    if(value != 0) max_bounces = value;
                } else if(argument == "--output" || argument == "-o") {
                    output_path = std::string(argv[i + 1]);
                } else if(argument == "--debug" || argument == "-d") {
                    debug_mode = str_to_lower(std::string(argv[i + 1]));
                }
            }
            if(argument == "--nobvh" || argument == "-n") {
                no_bvh = true;
            }
        }
    }

    // Create and setup the scene
    std::cout << "Setting up scene: " << scene_name << std::endl;
    Scene scene;
    scene.set_use_bvh(!no_bvh);

    // Triangle Tests
    if(scene_name == "tri_test0.0") setup_triangle_test_scene(scene, 4, 4, 0);
    else if(scene_name == "tri_test0.1") setup_triangle_test_scene(scene, 128, 128, 0);
    else if(scene_name == "tri_test1.0") setup_triangle_test_scene(scene, 4, 4, 1);
    else if(scene_name == "tri_test1.1") setup_triangle_test_scene(scene, 128, 128, 1);
    else if(scene_name == "tri_test2.0") setup_triangle_test_scene(scene, 4, 4, 2);
    else if(scene_name == "tri_test2.1") setup_triangle_test_scene(scene, 128, 128, 2);
    else if(scene_name == "tri_test3.0") setup_triangle_test_scene(scene, 4, 4, 3);
    else if(scene_name == "tri_test3.1") setup_triangle_test_scene(scene, 128, 128, 3);
    // Sphere Tests
    else if(scene_name == "sph_test0.0") setup_sphere_test_scene(scene, 4, 4, 0);
    else if(scene_name == "sph_test0.1") setup_sphere_test_scene(scene, 128, 128, 0);
    else if(scene_name == "sph_test1.0") setup_sphere_test_scene(scene, 4, 4, 1);
    else if(scene_name == "sph_test1.1") setup_sphere_test_scene(scene, 128, 128, 1);
    else if(scene_name == "sph_test2.0") setup_sphere_test_scene(scene, 4, 4, 2);
    else if(scene_name == "sph_test2.1") setup_sphere_test_scene(scene, 128, 128, 2);
    else if(scene_name == "sph_test3.0") setup_sphere_test_scene(scene, 4, 4, 3);
    else if(scene_name == "sph_test3.1") setup_sphere_test_scene(scene, 128, 128, 3);
    // Balls scenes
    else if(scene_name == "balls0") setup_balls_scene(scene, 0);
    else if(scene_name == "balls1") setup_balls_scene(scene, 1);
    else if(scene_name == "balls2") setup_balls_scene(scene, 2);
    // City scenes
    else if(scene_name == "city0") setup_city_scene(scene, 0);
    else if(scene_name == "city1") setup_city_scene(scene, 1);
    else if(scene_name == "city2") setup_city_scene(scene, 2);
    else if(scene_name == "city3") setup_city_scene(scene, 3);
    // Cornell Box scenes
    else if(scene_name == "cornell_box0") setup_cornell_box_scene(scene, 0);
    else if(scene_name == "cornell_box1") setup_cornell_box_scene(scene, 1);
    else if(scene_name == "cornell_box2") setup_cornell_box_scene(scene, 2);
    else if(scene_name == "cornell_box3") setup_cornell_box_scene(scene, 3);
    // Special scene
    else setup_special_scene(scene, scene_name);

    if(debug_mode == "distance") {

        // Debug draw hit distance
        std::cout << "Debug drawing hit distance for scene: " << scene_name << std::endl;
        Image result = debug_draw_hit_distance(scene);
        // Save the rendered scene
        if(output_path.empty()) output_path = scene_name + "-distance-debug.png";
        result.save(output_path);
        std::cout << "Result saved to " << output_path << std::endl;

    } else if(debug_mode == "normal") {

        // Debug draw hit normal
        std::cout << "Debug drawing hit normal for scene: " << scene_name << std::endl;
        Image result = debug_draw_hit_normal(scene);
        // Save the rendered scene
        if(output_path.empty()) output_path = scene_name + "-normal-debug.png";
        result.save(output_path);
        std::cout << "Result saved to " << output_path << std::endl;

    } else if(debug_mode == "none") {

        // Render the scene and track the elapsed time
        std::cout << "Rendering scene: " << scene_name << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        Image result = path_trace(scene, sample_count, max_bounces);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> seconds_duration = end - start;
        std::cout << "Total Render time: " << seconds_duration.count() << " seconds" << std::endl;

        // Save the rendered scene
        if(output_path.empty()) output_path = scene_name + ".png";
        result.save(output_path);
        std::cout << "Result saved to " << output_path << std::endl;

    } else {

        std::cout << "Invalid debug mode: " << debug_mode << std::endl;

    }

    return 0;
}