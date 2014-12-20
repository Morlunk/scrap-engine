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

#ifndef SRC_SCRAP_GL_REGISTRY_H_
#define SRC_SCRAP_GL_REGISTRY_H_

#include <string>
#include <vector>
#include "scrap/gl/shader.h"

namespace scrap {
namespace gl {

 // A registry for GL shader objects.
class Registry {
 public:
  Registry();

  // Attempts to load the shader at the given path.
  // The shader object is valid for the life of the registry.
  // Returns a pointer to the loaded shader if successful, NULL otherwise.
  Shader* LoadShader(ShaderType type, std::string path);
  // Frees the given shader, removing it from the registry.
  bool UnloadShader(Shader *shader);
 private:
  std::vector<Shader> shaders_;
};

}  // namespace gl
}  // namespace scrap

#endif  // SRC_SCRAP_GL_REGISTRY_H_
