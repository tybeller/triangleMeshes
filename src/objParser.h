#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

struct objParser {
    void parseFile(std::string name, std::vector<glm::vec3>& outVect);
};
