// Copyright © 2014 Andrew Comminos <andrew@morlunk.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "engine.h"

static GLFWwindow* window_;
static std::stack<scrap::Scene*> scene_stack_;

static void Loop();

void scrap::engine::Init(scrap::Scene *scene, scrap::Config config) {
    scene_stack_.push(scene);

    glfwInit();

    // TODO(andrew): ensure that config modes are sane.
    window_ = glfwCreateWindow(config.width(), config.height(),
                               "Scrapit", NULL, NULL);
    if (!window_) {
        glfwTerminate();
        return;
    }
    glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        scene_stack_.top()->OnKeyEvent(key, scancode, action, mods);
    });

    glfwMakeContextCurrent(window_);
    Loop();
}

void scrap::engine::Destroy() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void scrap::engine::Push(scrap::Scene *scene) {
    scene_stack_.push(scene);
}

void scrap::engine::Pop() {
    scene_stack_.pop();
    // TODO: destroy if out of scenes?
    // if (scene_stack_.empty()) {
    //     Destroy();
    // }
}

void Loop() {
    double delta_time, start_time;
    while (!glfwWindowShouldClose(window_)) {
        start_time = glfwGetTime();

        scrap::Scene *scene = scene_stack_.top();
        scene->Update(delta_time);
        scene->Render();

        glfwSwapBuffers(window_);
        glfwPollEvents();

        delta_time = glfwGetTime() - start_time;
    }
}
