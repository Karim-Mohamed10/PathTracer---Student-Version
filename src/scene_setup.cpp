#include "scene_setup.hpp"

void setup_triangle_test_scene(Scene& scene, int width, int height, int version) {
    scene.set_background(std::make_shared<SimpleBackground>(Colors::BLACK));
    scene.set_camera(Camera (
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::radians(90.0f),
        glm::ivec2(width, height)
    ));

    scene.start_construction();

    std::shared_ptr<Material> light = std::make_shared<EmissiveMaterial>(Color(1.0f, 1.0f, 1.0f) * 2.0f);

    if(version == 0) { // Fully visible triangle
        scene.add_triangle(light, glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.5f, 0.0f));
    } else if(version == 1) { // Slightly tilted up
        scene.add_triangle(light, glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.5f, -0.5f));
    } else if(version == 2) { // Parallel to camera direction
        scene.add_triangle(light, glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.0f, 0.5f));
    } else if(version == 3) { // Back of camera
        scene.add_triangle(light, glm::vec3(-0.5f, -0.5f, 2.0f), glm::vec3(0.5f, -0.5f, 2.0f), glm::vec3(0.0f, 0.5f, 2.0f));
    }

    scene.finish_construction();
}

void setup_sphere_test_scene(Scene& scene, int width, int height, int version) {
    scene.set_background(std::make_shared<SimpleBackground>(Colors::BLACK));
    scene.set_camera(Camera (
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::radians(90.0f),
        glm::ivec2(width, height)
    ));

    scene.start_construction();

    std::shared_ptr<Material> light = std::make_shared<EmissiveMaterial>(Color(1.0f, 1.0f, 1.0f) * 2.0f);

    if(version == 0) { // Fully visible sphere
        scene.add_sphere(light, glm::vec3(0.0f, 0.0f, 0.0f), 0.5f);
    } else if(version == 1) { // Slightly up
        scene.add_sphere(light, glm::vec3(0.0f, 0.1f, 0.0f), 0.5f);
    } else if(version == 2) { // Inside sphere
        scene.add_sphere(light, glm::vec3(0.0f, 0.0f, 1.0f), 0.5f);
    } else if(version == 3) { // Back of camera
        scene.add_sphere(light, glm::vec3(0.0f, 0.0f, 2.0f), 0.5f);
    }

    scene.finish_construction();
}

void setup_balls_scene(Scene& scene, int version) {
    scene.set_background(std::make_shared<SkyBackground>(
        Color(0.4f, 0.5f, 1.0f) * 2.0f, 
        Color(0.4f, 0.3f, 0.8f), 
        Color(0.2f, 0.2f, 0.3f),
        Color(1.0f, 0.9f, 0.9f) * 50.0f,
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::radians(30.0f)
    ));
    scene.set_camera(Camera (
        glm::vec3(0.0f, 1.0f, 4.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::radians(60.0f),
        glm::ivec2(256, 256)
    ));

    scene.start_construction();

    std::shared_ptr<Material> white = std::make_shared<LambertMaterial>(Color(0.8f, 0.8f, 0.8f));
    std::shared_ptr<Material> ground = std::make_shared<LambertMaterial>(Color(0.8f, 0.2f, 0.1f));
    std::shared_ptr<Material> silver = std::make_shared<SmoothMetalMaterial>(Color(0.3f, 0.4f, 0.5f));

    // Ground
    scene.add_rectangle(ground, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
    // Spheres
    scene.add_sphere(version > 0 ? silver : white, glm::vec3( 0.0f,  0.0f,  0.0f), 1.0f);
    scene.add_sphere(version > 1 ? silver : white, glm::vec3( 0.0f,  1.5f,  0.0f), 0.5f);
    scene.add_sphere(version > 1 ? silver : white, glm::vec3( 1.0f, -0.5f,  1.0f), 0.5f);
    scene.add_sphere(version > 1 ? silver : white, glm::vec3(-1.0f, -0.5f,  1.0f), 0.5f);
    scene.add_sphere(version > 1 ? silver : white, glm::vec3(-1.0f, -0.5f, -1.0f), 0.5f);
    scene.add_sphere(version > 1 ? silver : white, glm::vec3( 1.0f, -0.5f, -1.0f), 0.5f);

    scene.finish_construction();
}

void setup_city_scene(Scene& scene, int version) {
    if(version <= 1) {
        scene.set_background(std::make_shared<SkyBackground>(
            Color(0.4f, 0.5f, 1.0f) * 2.0f, 
            Color(0.4f, 0.3f, 0.8f), 
            Color(0.2f, 0.2f, 0.3f),
            Color(1.0f, 0.9f, 0.9f) * 100.0f,
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::radians(20.0f)
        ));
    } else {
        scene.set_background(std::make_shared<SimpleBackground>(Colors::BLACK));
    }
    scene.set_camera(Camera (
        glm::vec3(-6.0f, 6.0f, 10.0f),
        glm::vec3(0.0f, 2.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::radians(60.0f),
        glm::ivec2(256, 256)
    ));

    scene.start_construction();

    std::shared_ptr<Material> grey = std::make_shared<LambertMaterial>(Color(0.5f, 0.5f, 0.5f));
    std::shared_ptr<Material> ground = std::make_shared<LambertMaterial>(Color(0.8f, 0.2f, 0.1f));
    std::shared_ptr<Material> silver = std::make_shared<SmoothMetalMaterial>(Color(0.3f, 0.4f, 0.5f));
    std::shared_ptr<Material> light = std::make_shared<EmissiveMaterial>(Color(1.0f, 1.0f, 1.0f) * 5.0f);

    float heights[] = {
        3, 1, 4, 5,
        1, 5, 2, 4,
        1, 5, 5, 4,
        1, 5, 4, 4
    };

    // Ground
    scene.add_rectangle(ground, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1000.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
    
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            float height = heights[i * 4 + j];
            std::shared_ptr<Material> material = version % 2 == 0 ? grey : silver;
            scene.add_cuboid(material, glm::vec3(i * 2.0f - 3.0f, height * 0.5f, j * 2.0f - 3.0f), glm::vec3(1.0f, height, 1.0f));
        }
    }
    
    if(version > 1) {
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                if(i < 3) scene.add_sphere(light, glm::vec3(i * 2.0f - 2.0f, 0.5f, j * 2.0f - 3.0f), 0.25f);
                if(j < 3) scene.add_sphere(light, glm::vec3(i * 2.0f - 3.0f, 0.5f, j * 2.0f - 2.0f), 0.25f);
            }
        }
    }

    scene.finish_construction();
}

void setup_cornell_box_scene(Scene& scene, int version) {
    scene.set_background(std::make_shared<SimpleBackground>(Colors::BLACK));
    scene.set_camera(Camera (
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::radians(50.0f),
        glm::ivec2(256, 256)
    ));

    scene.start_construction();

    std::shared_ptr<Material> white = std::make_shared<LambertMaterial>(Color(0.8f, 0.8f, 0.8f));
    std::shared_ptr<Material> red = std::make_shared<LambertMaterial>(Color(0.8f, 0.0f, 0.0f));
    std::shared_ptr<Material> green = std::make_shared<LambertMaterial>(Color(0.0f, 0.8f, 0.0f));
    std::shared_ptr<Material> light = std::make_shared<EmissiveMaterial>(Color(1.0f, 1.0f, 1.0f) * 5.0f);
    std::shared_ptr<Material> gold = std::make_shared<SmoothMetalMaterial>(Colors::YELLOW);

    // Back Face
    scene.add_rectangle(white, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(2.0f, 2.0f), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
    // Top Face
    scene.add_rectangle(white, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
    // Bottom Face
    scene.add_rectangle(white, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
    // Right Face
    scene.add_rectangle(green, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(2.0f, 2.0f), glm::vec3(0.0f, glm::radians(90.0f), 0.0f)); 
    // Left face
    scene.add_rectangle(red, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(2.0f, 2.0f), glm::vec3(0.0f, glm::radians(90.0f), 0.0f)); 
    // cuboids
    scene.add_cuboid(white, glm::vec3(0.468f, -0.7f, 0.216f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.0f, 0.0f, -0.314f));
    scene.add_cuboid(white, glm::vec3(-0.36f, -0.4f, -0.252f), glm::vec3(0.6f, 1.2f, 0.6f), glm::vec3(0.0f, 0.0f, 0.3925f));
    
    // Light
    if(version <= 1) {
        scene.add_rectangle(light, glm::vec3(0.0f, 0.999f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));     
    } else {
        // scene.add_rectangle(light, glm::vec3( 0.98f, -0.98f, 0.0f), glm::vec2(0.2f, 2.0f), glm::vec3(0.0f, glm::radians(45.0f), 0.0f));
        // scene.add_rectangle(light, glm::vec3(-0.98f, -0.98f, 0.0f), glm::vec2(0.2f, 2.0f), glm::vec3(0.0f, glm::radians(-45.0f), 0.0f));
        scene.add_sphere(light, glm::vec3(0.5f, -0.75f, -0.5f), 0.25f);
    }
    
    // Sphere
    if(version % 2 == 1) scene.add_sphere(gold, glm::vec3(0.468f, -0.1f, 0.216f), 0.3f);

    scene.finish_construction();
}

void setup_special_scene(Scene& scene, const std::string& name) {
    uint64_t font[256] = {};
    font['0'] = 0x3c'66'6e'7e'76'66'3e'00;
    font['1'] = 0x18'78'18'18'18'18'7e'00;
    font['2'] = 0x3c'66'06'1c'30'66'7e'00;
    font['3'] = 0x3c'66'06'1c'06'66'7e'00;
    font['4'] = 0x1c'3c'6c'cc'fe'0c'0c'00;
    font['5'] = 0x7e'60'7c'06'06'66'3c'00;
    font['6'] = 0x1c'30'60'7c'66'66'3c'00;
    font['7'] = 0x7e'66'06'0c'18'30'30'00;
    font['8'] = 0x3c'66'66'3c'66'66'3c'00;
    font['9'] = 0x3c'66'66'3e'06'0c'38'00;
    font['/'] = 0x03'07'0e'1c'38'70'f0'c0;
    font['\\'] = 0xc0'f0'70'38'1c'0e'07'03;
    font['@'] = 0x3c'66'6e'6e'60'62'3e'00;
    font['a'] = font['A'] = 0x18'3c'66'7e'66'66'66'00;
    font['b'] = font['B'] = 0x7c'66'66'7c'66'66'7c'00;
    font['c'] = font['C'] = 0x3c'66'60'60'60'66'3c'00;
    font['d'] = font['D'] = 0x78'6c'66'66'66'6c'78'00;
    font['e'] = font['E'] = 0x7e'60'60'78'60'60'7e'00;
    font['f'] = font['F'] = 0x7e'60'60'78'60'60'60'00;
    font['g'] = font['G'] = 0x3c'66'60'6e'66'66'3c'00;
    font['h'] = font['H'] = 0x66'66'66'7e'66'66'66'00;
    font['i'] = font['I'] = 0x3c'18'18'18'18'18'3c'00;
    font['j'] = font['J'] = 0x1e'0c'0c'0c'0c'6c'38'00;
    font['k'] = font['K'] = 0x66'6c'78'70'78'6c'66'00;
    font['l'] = font['L'] = 0x60'60'60'60'60'60'7e'00;
    font['m'] = font['M'] = 0x63'77'7f'6b'63'63'63'00;
    font['n'] = font['N'] = 0x66'76'7e'7e'6e'66'66'00;
    font['o'] = font['O'] = 0x3c'66'66'66'66'66'3c'00;
    font['p'] = font['P'] = 0x7c'66'66'7c'60'60'60'00;
    font['q'] = font['Q'] = 0x3c'66'66'66'66'3c'0e'00;
    font['r'] = font['R'] = 0x7c'66'66'7c'78'6c'66'00;
    font['s'] = font['S'] = 0x3c'66'60'3c'06'66'3c'00;
    font['t'] = font['T'] = 0x7e'18'18'18'18'18'18'00;
    font['u'] = font['U'] = 0x66'66'66'66'66'66'3c'00;
    font['v'] = font['V'] = 0x66'66'66'66'66'3c'18'00;
    font['w'] = font['W'] = 0x63'63'63'6b'7f'77'63'00;
    font['x'] = font['X'] = 0x66'66'3c'18'3c'66'66'00;
    font['y'] = font['Y'] = 0x66'66'66'3c'18'18'18'00;
    font['z'] = font['Z'] = 0x7e'06'0c'18'30'60'7e'00;
    font['!'] = 0x18'3c'3c'18'18'00'18'00;
    font['?'] = 0x7e'66'06'0c'18'00'10'00;
    font['#'] = 0x66'66'ff'66'ff'66'66'00;
    font['$'] = 0x18'3e'60'3c'06'7c'18'00;
    font['%'] = 0x62'66'0c'18'30'66'46'00;
    font['&'] = 0x3c'66'3c'38'67'66'3f'00;
    font['('] = 0x0c'18'30'30'30'18'0c'00;
    font[')'] = 0x30'18'0c'0c'0c'18'30'00;
    font['{'] = 0x1c'30'30'60'30'30'1c'00;
    font['}'] = 0x38'0c'0c'06'0c'0c'38'00;
    font['['] = 0x3c'30'30'30'30'30'3c'00;
    font[']'] = 0x3c'0c'0c'0c'0c'0c'3c'00;
    font['|'] = 0x18'18'18'18'18'18'18'00;
    font['*'] = 0x00'66'3c'ff'3c'66'00'00;
    font[':'] = 0x00'00'18'00'00'18'00'00;
    font['.'] = 0x00'00'00'18'18'00'00'00;
    font[','] = 0x00'00'00'18'18'30'00'00;
    font['"'] = 0x66'66'66'00'00'00'00'00;
    font['-'] = 0x00'00'00'7e'00'00'00'00;
    font['_'] = 0x00'00'00'00'00'00'00'7e;
    font['~'] = 0x00'00'76'fe'dc'00'00'00;
    font['`'] = 0x60'30'18'00'00'00'00'00;
    font['+'] = 0x00'18'18'7e'18'18'00'00;
    font['='] = 0x00'00'7e'00'7e'00'00'00;
    font['\''] = 0x06'0c'18'00'00'00'00'00;

    uint32_t seed = 2166136261UL;
    for(char c: name) seed = (seed ^ c) * 16777619;
    auto get_rand = [&seed]() {seed = seed * 1103515245 + 12345; return seed % 32768;};

    scene.set_background(std::make_shared<SimpleBackground>(Colors::BLACK));
    scene.set_camera(Camera (
        glm::vec3(0.0f, 0.0f, 150.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::radians(50.0f),
        glm::ivec2(256, 256)
    ));

    scene.start_construction();

    std::shared_ptr<Material> white = std::make_shared<LambertMaterial>(Color(0.8f, 0.8f, 0.8f));
    std::shared_ptr<Material> light = std::make_shared<EmissiveMaterial>(Color(0.9f, 0.9f, 0.9f) * 5.0f);
    
    int name_length = 0;
    while(name_length < name.length() && name[name_length] != '_') name_length++;

    std::string lines[] = { "is awesome", name.substr(0, name_length)};

    for(int line_index = 0; line_index < 2; line_index++) {
        const std::string& line = lines[line_index];
        int length = line.length();
        glm::vec3 start_point = glm::vec3(-3.5f - 4.0f * (length - 1), -10.0f + 12.0f * line_index, 0.0f);
        for(int char_index = 0; char_index < line.size(); char_index++) {
            uint64_t mask = font[line[char_index]];
            if(mask == 0) continue;
            for(int row = 0; row < 8; row++) {
                for(int col = 0; col < 8; col++) {
                    uint64_t bit = 1ULL << (row * 8 + 7 - col);
                    if((mask & bit) == 0) continue;
                    scene.add_rectangle(light, start_point + glm::vec3(char_index * 8 + col, row, -49.99f), glm::vec2(1.0f, 1.0f), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
                }
            }
        }
    }

    
    std::shared_ptr<Material> right_mat = std::make_shared<LambertMaterial>(convert_HSL_to_RGB(get_rand() / 32767.0f, 1.0f, 0.5f));
    std::shared_ptr<Material> left_mat = std::make_shared<LambertMaterial>(convert_HSL_to_RGB(get_rand() / 32767.0f, 1.0f, 0.5f));
    
    // Back Face
    scene.add_rectangle(white, glm::vec3(0.0f, 0.0f, -50.0f), glm::vec2(100.0f, 100.0f), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f));
    // Top Face
    scene.add_rectangle(white, glm::vec3(0.0f, 50.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    // Bottom Face
    scene.add_rectangle(white, glm::vec3(0.0f, -50.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::vec3(0.0f, 0.0f, 0.0f)); 
    // Right Face
    scene.add_rectangle(right_mat, glm::vec3(50.0f, 0.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::vec3(0.0f, glm::radians(90.0f), 0.0f)); 
    // Left face
    scene.add_rectangle(left_mat, glm::vec3(-50.0f, 0.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::vec3(0.0f, glm::radians(90.0f), 0.0f)); 
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            float radius = glm::mix(5.0f, 10.0f, get_rand() / 32767.0f);
            float x = -50.0f + i * 25.0f + glm::mix(radius, 25.0f - radius, get_rand() / 32767.0f);
            float y = -50.0f + radius;
            float z = -50.0f + j * 25.0f + glm::mix(radius, 25.0f - radius, get_rand() / 32767.0f);
            Color color = convert_HSL_to_RGB(get_rand() / 32767.0f, 0.5f, 0.5f);
            std::shared_ptr<Material> sphere_mat;
            if(get_rand() % 2)
                sphere_mat = std::make_shared<LambertMaterial>(color);
            else 
                sphere_mat = std::make_shared<SmoothMetalMaterial>(color);
            scene.add_sphere(sphere_mat, glm::vec3(x, y, z), radius);
        }
    }

    scene.finish_construction();
}