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

#include "scrap/scene/model_scene.h"
#include <iterator>
#include <cassert>
#include "scrap/gl/gl_config.h"
#include "scrap/engine.h"

scrap::ModelScene::ModelScene() {
}

void scrap::ModelScene::OnShow() {
    default_program_ = new gl::Program();
    gl::Shader vert_shader(gl::VertexShader);
    gl::Shader frag_shader(gl::FragmentShader);
    // FIXME(andrew): example code
    vert_shader.Compile(
        "#version 100\n"
        "uniform mat4 u_mvp;\n"
        "in vec3 a_pos;\n"
        "in vec2 a_uv;\n"
        "varying vec2 v_texcoord;\n"
        "void main(void) {\n"
        "   gl_Position = u_mvp * vec4(a_pos, 1.0);\n"
        "   v_texcoord = a_uv;\n"
        "}");
    frag_shader.Compile(
        "#version 100\n"
        "precision mediump float;\n"
        "uniform sampler2D u_tex;\n"
        "in vec2 v_texcoord;\n"
        "void main() {\n"
        "    vec4 color = texture2D(u_tex, v_texcoord);\n"
        "    gl_FragColor = color; // TODO: shading\n"
        "}");
    default_program_->Link(vert_shader, frag_shader);

    renderer_ = new Renderer(scrap::engine::Width(), scrap::engine::Height());
    renderer_->SetDefaultProgram(default_program_);
}

void scrap::ModelScene::Render() {
    assert(renderer_);  // if this throws, it's a scene lifecycle issue
    renderer_->Render(*this);
}

void scrap::ModelScene::OnHide() {
    delete renderer_;
}

void scrap::ModelScene::OnSizeChange(int width, int height) {
    active_camera_->set_ratio((float)width/(float)height);
    renderer_->Resize(width, height);
}
