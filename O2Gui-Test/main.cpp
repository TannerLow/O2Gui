#include <SFML/Graphics.hpp>
#include "GraphicsManager.h"
#include <iostream>
#include <filesystem>
#include "ScrollDirection.h"
#include "ScrollBarTextures.h"
#include "RateLimiter.h"

#include "Text.h"

namespace fs = std::filesystem;

void buttonClickedMessage() {
    std::cout << "Button Clicked" << std::endl;
}

std::map<int, fs::path> generateMinecraftFontImagePaths();

int main() {
    RateLimiter drawLimiter(250);
    sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "SFML works!");

    GraphicsManager graphicsManager;
    
    auto button = graphicsManager.createButton();
    button->x = 10;
    button->y = 20;
    button->width = 200;
    button->height = 100;
    button->color = Color(sf::Color::Green);
    button->render();
    button->setOnClick(buttonClickedMessage);

    auto image = graphicsManager.createImage(fs::path("resources/double_shottys.png"));
    image->x = 0;
    image->y = 0;
    image->width = 200;
    image->height = 600;
    image->owned = true;
    image->render();

    auto temp = graphicsManager.createButton();
    temp->x = 390;
    temp->y = 290;
    temp->width = 220;
    temp->height = 220;
    temp->color = Color(sf::Color::Red);
    temp->render();

    auto minecraftFont = graphicsManager.loadFont(
        "minecraft_unicode",
        { 16, 16 },
        { 16, 16 },
        "resources/fonts/minecraft_unicode/font_widths.dat",
        generateMinecraftFontImagePaths()
    );

    auto text = graphicsManager.createText("minecraft_unicode");
    text->text = "Hello world";
    text->owned = true;
    text->render();

    ScrollBarTextures scrollBarTextures;
    scrollBarTextures.increase = fs::path("resources/gray_scroll_down.png");
    scrollBarTextures.bar = fs::path("resources/gray_scroll_bar.png");
    scrollBarTextures.barBackground = fs::path("resources/gray_scroll_bar_bg.png");
    scrollBarTextures.decrease = fs::path("resources/gray_scroll_up.png");
    auto scrollPanel = graphicsManager.createScrollPanel(scrollBarTextures);
    scrollPanel->x = 400;
    scrollPanel->y = 300;
    scrollPanel->maxHeight = 600;
    scrollPanel->visibleWidth = 200;
    scrollPanel->visibleHeight = 200;
    scrollPanel->elements["image"] = image;
    scrollPanel->elements["text"] = text;
    scrollPanel->render();

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    std::cout << "mouse click  : (" << mouseButtonPressed->position.x << ", " << mouseButtonPressed->position.y << ")" << std::endl;
                    sf::Vector2f coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    button->handleClick(coords.x, coords.y);
                    scrollPanel->handleClick(coords.x, coords.y);
                }
            }
            else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseButtonReleased->button == sf::Mouse::Button::Left) {
                    std::cout << "mouse release: (" << mouseButtonReleased->position.x << ", " << mouseButtonReleased->position.y << ")" << std::endl;
                    sf::Vector2f coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    scrollPanel->handleClickRelease(coords.x, coords.y);
                }
            }
            else if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
                ScrollDirection direction = ScrollDirection::DOWN;
                if (mouseWheelScrolled->delta > 0) {
                    direction = ScrollDirection::UP;
                }

                scrollPanel->handleScroll(direction);
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                    std::cout << "the escape key was pressed" << std::endl;
                    std::cout << "scancode: " << static_cast<int>(keyPressed->scancode) << std::endl;
                    std::cout << "code: " << static_cast<int>(keyPressed->code) << std::endl;
                    std::cout << "control: " << keyPressed->control << std::endl;
                    std::cout << "alt: " << keyPressed->alt << std::endl;
                    std::cout << "shift: " << keyPressed->shift << std::endl;
                    std::cout << "system: " << keyPressed->system << std::endl;
                    std::cout << "description: " << sf::Keyboard::getDescription(keyPressed->scancode).toAnsiString() << std::endl;
                    std::cout << "localize: " << static_cast<int>(sf::Keyboard::localize(keyPressed->scancode)) << std::endl;
                    std::cout << "delocalize: " << static_cast<int>(sf::Keyboard::delocalize(keyPressed->code)) << std::endl;
                }
                std::cout << "Key pressed event" << std::endl;
            }
            else if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
                if (textEntered->unicode < 128) {
                    std::cout << "ASCII character typed: " << static_cast<char>(textEntered->unicode) << std::endl;
                }
            }
        }

        sf::Vector2f mouseCoords = sf::Vector2f(sf::Mouse::getPosition(window));
        scrollPanel->update(mouseCoords.x, mouseCoords.y);

        if (drawLimiter.isReady()) {
            window.clear();
            window.draw(graphicsManager);
            window.display();
        }
    }
}

std::map<int, fs::path> generateMinecraftFontImagePaths() {
    return std::map<int, fs::path>{
        { 0x00, fs::path("resources/fonts/minecraft_unicode/unicode_page_00.png") },
        { 0x01, fs::path("resources/fonts/minecraft_unicode/unicode_page_01.png") },
        { 0x02, fs::path("resources/fonts/minecraft_unicode/unicode_page_02.png") },
        { 0x03, fs::path("resources/fonts/minecraft_unicode/unicode_page_03.png") },
        { 0x04, fs::path("resources/fonts/minecraft_unicode/unicode_page_04.png") },
        { 0x05, fs::path("resources/fonts/minecraft_unicode/unicode_page_05.png") },
        { 0x06, fs::path("resources/fonts/minecraft_unicode/unicode_page_06.png") },
        { 0x07, fs::path("resources/fonts/minecraft_unicode/unicode_page_07.png") },
        { 0x09, fs::path("resources/fonts/minecraft_unicode/unicode_page_09.png") },
        { 0x0a, fs::path("resources/fonts/minecraft_unicode/unicode_page_0a.png") },
        { 0x0b, fs::path("resources/fonts/minecraft_unicode/unicode_page_0b.png") },
        { 0x0c, fs::path("resources/fonts/minecraft_unicode/unicode_page_0c.png") },
        { 0x0d, fs::path("resources/fonts/minecraft_unicode/unicode_page_0d.png") },
        { 0x0e, fs::path("resources/fonts/minecraft_unicode/unicode_page_0e.png") },
        { 0x0f, fs::path("resources/fonts/minecraft_unicode/unicode_page_0f.png") },
        { 0x10, fs::path("resources/fonts/minecraft_unicode/unicode_page_10.png") },
        { 0x11, fs::path("resources/fonts/minecraft_unicode/unicode_page_11.png") },
        { 0x12, fs::path("resources/fonts/minecraft_unicode/unicode_page_12.png") },
        { 0x13, fs::path("resources/fonts/minecraft_unicode/unicode_page_13.png") },
        { 0x14, fs::path("resources/fonts/minecraft_unicode/unicode_page_14.png") },
        { 0x15, fs::path("resources/fonts/minecraft_unicode/unicode_page_15.png") },
        { 0x16, fs::path("resources/fonts/minecraft_unicode/unicode_page_16.png") },
        { 0x17, fs::path("resources/fonts/minecraft_unicode/unicode_page_17.png") },
        { 0x18, fs::path("resources/fonts/minecraft_unicode/unicode_page_18.png") },
        { 0x19, fs::path("resources/fonts/minecraft_unicode/unicode_page_19.png") },
        { 0x1a, fs::path("resources/fonts/minecraft_unicode/unicode_page_1a.png") },
        { 0x1b, fs::path("resources/fonts/minecraft_unicode/unicode_page_1b.png") },
        { 0x1c, fs::path("resources/fonts/minecraft_unicode/unicode_page_1c.png") },
        { 0x1d, fs::path("resources/fonts/minecraft_unicode/unicode_page_1d.png") },
        { 0x1e, fs::path("resources/fonts/minecraft_unicode/unicode_page_1e.png") },
        { 0x1f, fs::path("resources/fonts/minecraft_unicode/unicode_page_1f.png") },
        { 0x20, fs::path("resources/fonts/minecraft_unicode/unicode_page_20.png") },
        { 0x21, fs::path("resources/fonts/minecraft_unicode/unicode_page_21.png") },
        { 0x22, fs::path("resources/fonts/minecraft_unicode/unicode_page_22.png") },
        { 0x23, fs::path("resources/fonts/minecraft_unicode/unicode_page_23.png") },
        { 0x24, fs::path("resources/fonts/minecraft_unicode/unicode_page_24.png") },
        { 0x25, fs::path("resources/fonts/minecraft_unicode/unicode_page_25.png") },
        { 0x26, fs::path("resources/fonts/minecraft_unicode/unicode_page_26.png") },
        { 0x27, fs::path("resources/fonts/minecraft_unicode/unicode_page_27.png") },
        { 0x28, fs::path("resources/fonts/minecraft_unicode/unicode_page_28.png") },
        { 0x29, fs::path("resources/fonts/minecraft_unicode/unicode_page_29.png") },
        { 0x2a, fs::path("resources/fonts/minecraft_unicode/unicode_page_2a.png") },
        { 0x2b, fs::path("resources/fonts/minecraft_unicode/unicode_page_2b.png") },
        { 0x2c, fs::path("resources/fonts/minecraft_unicode/unicode_page_2c.png") },
        { 0x2d, fs::path("resources/fonts/minecraft_unicode/unicode_page_2d.png") },
        { 0x2e, fs::path("resources/fonts/minecraft_unicode/unicode_page_2e.png") },
        { 0x2f, fs::path("resources/fonts/minecraft_unicode/unicode_page_2f.png") },
        { 0x30, fs::path("resources/fonts/minecraft_unicode/unicode_page_30.png") },
        { 0x31, fs::path("resources/fonts/minecraft_unicode/unicode_page_31.png") },
        { 0x32, fs::path("resources/fonts/minecraft_unicode/unicode_page_32.png") },
        { 0x33, fs::path("resources/fonts/minecraft_unicode/unicode_page_33.png") },
        { 0x34, fs::path("resources/fonts/minecraft_unicode/unicode_page_34.png") },
        { 0x35, fs::path("resources/fonts/minecraft_unicode/unicode_page_35.png") },
        { 0x36, fs::path("resources/fonts/minecraft_unicode/unicode_page_36.png") },
        { 0x37, fs::path("resources/fonts/minecraft_unicode/unicode_page_37.png") },
        { 0x38, fs::path("resources/fonts/minecraft_unicode/unicode_page_38.png") },
        { 0x39, fs::path("resources/fonts/minecraft_unicode/unicode_page_39.png") },
        { 0x3a, fs::path("resources/fonts/minecraft_unicode/unicode_page_3a.png") },
        { 0x3b, fs::path("resources/fonts/minecraft_unicode/unicode_page_3b.png") },
        { 0x3c, fs::path("resources/fonts/minecraft_unicode/unicode_page_3c.png") },
        { 0x3d, fs::path("resources/fonts/minecraft_unicode/unicode_page_3d.png") },
        { 0x3e, fs::path("resources/fonts/minecraft_unicode/unicode_page_3e.png") },
        { 0x3f, fs::path("resources/fonts/minecraft_unicode/unicode_page_3f.png") },
        { 0x40, fs::path("resources/fonts/minecraft_unicode/unicode_page_40.png") },
        { 0x41, fs::path("resources/fonts/minecraft_unicode/unicode_page_41.png") },
        { 0x42, fs::path("resources/fonts/minecraft_unicode/unicode_page_42.png") },
        { 0x43, fs::path("resources/fonts/minecraft_unicode/unicode_page_43.png") },
        { 0x44, fs::path("resources/fonts/minecraft_unicode/unicode_page_44.png") },
        { 0x45, fs::path("resources/fonts/minecraft_unicode/unicode_page_45.png") },
        { 0x46, fs::path("resources/fonts/minecraft_unicode/unicode_page_46.png") },
        { 0x47, fs::path("resources/fonts/minecraft_unicode/unicode_page_47.png") },
        { 0x48, fs::path("resources/fonts/minecraft_unicode/unicode_page_48.png") },
        { 0x49, fs::path("resources/fonts/minecraft_unicode/unicode_page_49.png") },
        { 0x4a, fs::path("resources/fonts/minecraft_unicode/unicode_page_4a.png") },
        { 0x4b, fs::path("resources/fonts/minecraft_unicode/unicode_page_4b.png") },
        { 0x4c, fs::path("resources/fonts/minecraft_unicode/unicode_page_4c.png") },
        { 0x4d, fs::path("resources/fonts/minecraft_unicode/unicode_page_4d.png") },
        { 0x4e, fs::path("resources/fonts/minecraft_unicode/unicode_page_4e.png") },
        { 0x4f, fs::path("resources/fonts/minecraft_unicode/unicode_page_4f.png") },
        { 0x50, fs::path("resources/fonts/minecraft_unicode/unicode_page_50.png") },
        { 0x51, fs::path("resources/fonts/minecraft_unicode/unicode_page_51.png") },
        { 0x52, fs::path("resources/fonts/minecraft_unicode/unicode_page_52.png") },
        { 0x53, fs::path("resources/fonts/minecraft_unicode/unicode_page_53.png") },
        { 0x54, fs::path("resources/fonts/minecraft_unicode/unicode_page_54.png") },
        { 0x55, fs::path("resources/fonts/minecraft_unicode/unicode_page_55.png") },
        { 0x56, fs::path("resources/fonts/minecraft_unicode/unicode_page_56.png") },
        { 0x57, fs::path("resources/fonts/minecraft_unicode/unicode_page_57.png") },
        { 0x58, fs::path("resources/fonts/minecraft_unicode/unicode_page_58.png") },
        { 0x59, fs::path("resources/fonts/minecraft_unicode/unicode_page_59.png") },
        { 0x5a, fs::path("resources/fonts/minecraft_unicode/unicode_page_5a.png") },
        { 0x5b, fs::path("resources/fonts/minecraft_unicode/unicode_page_5b.png") },
        { 0x5c, fs::path("resources/fonts/minecraft_unicode/unicode_page_5c.png") },
        { 0x5d, fs::path("resources/fonts/minecraft_unicode/unicode_page_5d.png") },
        { 0x5e, fs::path("resources/fonts/minecraft_unicode/unicode_page_5e.png") },
        { 0x5f, fs::path("resources/fonts/minecraft_unicode/unicode_page_5f.png") },
        { 0x60, fs::path("resources/fonts/minecraft_unicode/unicode_page_60.png") },
        { 0x61, fs::path("resources/fonts/minecraft_unicode/unicode_page_61.png") },
        { 0x62, fs::path("resources/fonts/minecraft_unicode/unicode_page_62.png") },
        { 0x63, fs::path("resources/fonts/minecraft_unicode/unicode_page_63.png") },
        { 0x64, fs::path("resources/fonts/minecraft_unicode/unicode_page_64.png") },
        { 0x65, fs::path("resources/fonts/minecraft_unicode/unicode_page_65.png") },
        { 0x66, fs::path("resources/fonts/minecraft_unicode/unicode_page_66.png") },
        { 0x67, fs::path("resources/fonts/minecraft_unicode/unicode_page_67.png") },
        { 0x68, fs::path("resources/fonts/minecraft_unicode/unicode_page_68.png") },
        { 0x69, fs::path("resources/fonts/minecraft_unicode/unicode_page_69.png") },
        { 0x6a, fs::path("resources/fonts/minecraft_unicode/unicode_page_6a.png") },
        { 0x6b, fs::path("resources/fonts/minecraft_unicode/unicode_page_6b.png") },
        { 0x6c, fs::path("resources/fonts/minecraft_unicode/unicode_page_6c.png") },
        { 0x6d, fs::path("resources/fonts/minecraft_unicode/unicode_page_6d.png") },
        { 0x6e, fs::path("resources/fonts/minecraft_unicode/unicode_page_6e.png") },
        { 0x6f, fs::path("resources/fonts/minecraft_unicode/unicode_page_6f.png") },
        { 0x70, fs::path("resources/fonts/minecraft_unicode/unicode_page_70.png") },
        { 0x71, fs::path("resources/fonts/minecraft_unicode/unicode_page_71.png") },
        { 0x72, fs::path("resources/fonts/minecraft_unicode/unicode_page_72.png") },
        { 0x73, fs::path("resources/fonts/minecraft_unicode/unicode_page_73.png") },
        { 0x74, fs::path("resources/fonts/minecraft_unicode/unicode_page_74.png") },
        { 0x75, fs::path("resources/fonts/minecraft_unicode/unicode_page_75.png") },
        { 0x76, fs::path("resources/fonts/minecraft_unicode/unicode_page_76.png") },
        { 0x77, fs::path("resources/fonts/minecraft_unicode/unicode_page_77.png") },
        { 0x78, fs::path("resources/fonts/minecraft_unicode/unicode_page_78.png") },
        { 0x79, fs::path("resources/fonts/minecraft_unicode/unicode_page_79.png") },
        { 0x7a, fs::path("resources/fonts/minecraft_unicode/unicode_page_7a.png") },
        { 0x7b, fs::path("resources/fonts/minecraft_unicode/unicode_page_7b.png") },
        { 0x7c, fs::path("resources/fonts/minecraft_unicode/unicode_page_7c.png") },
        { 0x7d, fs::path("resources/fonts/minecraft_unicode/unicode_page_7d.png") },
        { 0x7e, fs::path("resources/fonts/minecraft_unicode/unicode_page_7e.png") },
        { 0x7f, fs::path("resources/fonts/minecraft_unicode/unicode_page_7f.png") },
        { 0x80, fs::path("resources/fonts/minecraft_unicode/unicode_page_80.png") },
        { 0x81, fs::path("resources/fonts/minecraft_unicode/unicode_page_81.png") },
        { 0x82, fs::path("resources/fonts/minecraft_unicode/unicode_page_82.png") },
        { 0x83, fs::path("resources/fonts/minecraft_unicode/unicode_page_83.png") },
        { 0x84, fs::path("resources/fonts/minecraft_unicode/unicode_page_84.png") },
        { 0x85, fs::path("resources/fonts/minecraft_unicode/unicode_page_85.png") },
        { 0x86, fs::path("resources/fonts/minecraft_unicode/unicode_page_86.png") },
        { 0x87, fs::path("resources/fonts/minecraft_unicode/unicode_page_87.png") },
        { 0x88, fs::path("resources/fonts/minecraft_unicode/unicode_page_88.png") },
        { 0x89, fs::path("resources/fonts/minecraft_unicode/unicode_page_89.png") },
        { 0x8a, fs::path("resources/fonts/minecraft_unicode/unicode_page_8a.png") },
        { 0x8b, fs::path("resources/fonts/minecraft_unicode/unicode_page_8b.png") },
        { 0x8c, fs::path("resources/fonts/minecraft_unicode/unicode_page_8c.png") },
        { 0x8d, fs::path("resources/fonts/minecraft_unicode/unicode_page_8d.png") },
        { 0x8e, fs::path("resources/fonts/minecraft_unicode/unicode_page_8e.png") },
        { 0x8f, fs::path("resources/fonts/minecraft_unicode/unicode_page_8f.png") },
        { 0x90, fs::path("resources/fonts/minecraft_unicode/unicode_page_90.png") },
        { 0x91, fs::path("resources/fonts/minecraft_unicode/unicode_page_91.png") },
        { 0x92, fs::path("resources/fonts/minecraft_unicode/unicode_page_92.png") },
        { 0x93, fs::path("resources/fonts/minecraft_unicode/unicode_page_93.png") },
        { 0x94, fs::path("resources/fonts/minecraft_unicode/unicode_page_94.png") },
        { 0x95, fs::path("resources/fonts/minecraft_unicode/unicode_page_95.png") },
        { 0x96, fs::path("resources/fonts/minecraft_unicode/unicode_page_96.png") },
        { 0x97, fs::path("resources/fonts/minecraft_unicode/unicode_page_97.png") },
        { 0x98, fs::path("resources/fonts/minecraft_unicode/unicode_page_98.png") },
        { 0x99, fs::path("resources/fonts/minecraft_unicode/unicode_page_99.png") },
        { 0x9a, fs::path("resources/fonts/minecraft_unicode/unicode_page_9a.png") },
        { 0x9b, fs::path("resources/fonts/minecraft_unicode/unicode_page_9b.png") },
        { 0x9c, fs::path("resources/fonts/minecraft_unicode/unicode_page_9c.png") },
        { 0x9d, fs::path("resources/fonts/minecraft_unicode/unicode_page_9d.png") },
        { 0x9e, fs::path("resources/fonts/minecraft_unicode/unicode_page_9e.png") },
        { 0x9f, fs::path("resources/fonts/minecraft_unicode/unicode_page_9f.png") },
        { 0xa0, fs::path("resources/fonts/minecraft_unicode/unicode_page_a0.png") },
        { 0xa1, fs::path("resources/fonts/minecraft_unicode/unicode_page_a1.png") },
        { 0xa2, fs::path("resources/fonts/minecraft_unicode/unicode_page_a2.png") },
        { 0xa3, fs::path("resources/fonts/minecraft_unicode/unicode_page_a3.png") },
        { 0xa4, fs::path("resources/fonts/minecraft_unicode/unicode_page_a4.png") },
        { 0xa5, fs::path("resources/fonts/minecraft_unicode/unicode_page_a5.png") },
        { 0xa6, fs::path("resources/fonts/minecraft_unicode/unicode_page_a6.png") },
        { 0xa7, fs::path("resources/fonts/minecraft_unicode/unicode_page_a7.png") },
        { 0xa8, fs::path("resources/fonts/minecraft_unicode/unicode_page_a8.png") },
        { 0xa9, fs::path("resources/fonts/minecraft_unicode/unicode_page_a9.png") },
        { 0xaa, fs::path("resources/fonts/minecraft_unicode/unicode_page_aa.png") },
        { 0xab, fs::path("resources/fonts/minecraft_unicode/unicode_page_ab.png") },
        { 0xac, fs::path("resources/fonts/minecraft_unicode/unicode_page_ac.png") },
        { 0xad, fs::path("resources/fonts/minecraft_unicode/unicode_page_ad.png") },
        { 0xae, fs::path("resources/fonts/minecraft_unicode/unicode_page_ae.png") },
        { 0xaf, fs::path("resources/fonts/minecraft_unicode/unicode_page_af.png") },
        { 0xb0, fs::path("resources/fonts/minecraft_unicode/unicode_page_b0.png") },
        { 0xb1, fs::path("resources/fonts/minecraft_unicode/unicode_page_b1.png") },
        { 0xb2, fs::path("resources/fonts/minecraft_unicode/unicode_page_b2.png") },
        { 0xb3, fs::path("resources/fonts/minecraft_unicode/unicode_page_b3.png") },
        { 0xb4, fs::path("resources/fonts/minecraft_unicode/unicode_page_b4.png") },
        { 0xb5, fs::path("resources/fonts/minecraft_unicode/unicode_page_b5.png") },
        { 0xb6, fs::path("resources/fonts/minecraft_unicode/unicode_page_b6.png") },
        { 0xb7, fs::path("resources/fonts/minecraft_unicode/unicode_page_b7.png") },
        { 0xb8, fs::path("resources/fonts/minecraft_unicode/unicode_page_b8.png") },
        { 0xb9, fs::path("resources/fonts/minecraft_unicode/unicode_page_b9.png") },
        { 0xba, fs::path("resources/fonts/minecraft_unicode/unicode_page_ba.png") },
        { 0xbb, fs::path("resources/fonts/minecraft_unicode/unicode_page_bb.png") },
        { 0xbc, fs::path("resources/fonts/minecraft_unicode/unicode_page_bc.png") },
        { 0xbd, fs::path("resources/fonts/minecraft_unicode/unicode_page_bd.png") },
        { 0xbe, fs::path("resources/fonts/minecraft_unicode/unicode_page_be.png") },
        { 0xbf, fs::path("resources/fonts/minecraft_unicode/unicode_page_bf.png") },
        { 0xc0, fs::path("resources/fonts/minecraft_unicode/unicode_page_c0.png") },
        { 0xc1, fs::path("resources/fonts/minecraft_unicode/unicode_page_c1.png") },
        { 0xc2, fs::path("resources/fonts/minecraft_unicode/unicode_page_c2.png") },
        { 0xc3, fs::path("resources/fonts/minecraft_unicode/unicode_page_c3.png") },
        { 0xc4, fs::path("resources/fonts/minecraft_unicode/unicode_page_c4.png") },
        { 0xc5, fs::path("resources/fonts/minecraft_unicode/unicode_page_c5.png") },
        { 0xc6, fs::path("resources/fonts/minecraft_unicode/unicode_page_c6.png") },
        { 0xc7, fs::path("resources/fonts/minecraft_unicode/unicode_page_c7.png") },
        { 0xc8, fs::path("resources/fonts/minecraft_unicode/unicode_page_c8.png") },
        { 0xc9, fs::path("resources/fonts/minecraft_unicode/unicode_page_c9.png") },
        { 0xca, fs::path("resources/fonts/minecraft_unicode/unicode_page_ca.png") },
        { 0xcb, fs::path("resources/fonts/minecraft_unicode/unicode_page_cb.png") },
        { 0xcc, fs::path("resources/fonts/minecraft_unicode/unicode_page_cc.png") },
        { 0xcd, fs::path("resources/fonts/minecraft_unicode/unicode_page_cd.png") },
        { 0xce, fs::path("resources/fonts/minecraft_unicode/unicode_page_ce.png") },
        { 0xcf, fs::path("resources/fonts/minecraft_unicode/unicode_page_cf.png") },
        { 0xd0, fs::path("resources/fonts/minecraft_unicode/unicode_page_d0.png") },
        { 0xd1, fs::path("resources/fonts/minecraft_unicode/unicode_page_d1.png") },
        { 0xd2, fs::path("resources/fonts/minecraft_unicode/unicode_page_d2.png") },
        { 0xd3, fs::path("resources/fonts/minecraft_unicode/unicode_page_d3.png") },
        { 0xd4, fs::path("resources/fonts/minecraft_unicode/unicode_page_d4.png") },
        { 0xd5, fs::path("resources/fonts/minecraft_unicode/unicode_page_d5.png") },
        { 0xd6, fs::path("resources/fonts/minecraft_unicode/unicode_page_d6.png") },
        { 0xd7, fs::path("resources/fonts/minecraft_unicode/unicode_page_d7.png") },
        { 0xf9, fs::path("resources/fonts/minecraft_unicode/unicode_page_f9.png") },
        { 0xfa, fs::path("resources/fonts/minecraft_unicode/unicode_page_fa.png") },
        { 0xfb, fs::path("resources/fonts/minecraft_unicode/unicode_page_fb.png") },
        { 0xfc, fs::path("resources/fonts/minecraft_unicode/unicode_page_fc.png") },
        { 0xfd, fs::path("resources/fonts/minecraft_unicode/unicode_page_fd.png") },
        { 0xfe, fs::path("resources/fonts/minecraft_unicode/unicode_page_fe.png") },
        { 0xff, fs::path("resources/fonts/minecraft_unicode/unicode_page_ff.png") },
    };
}