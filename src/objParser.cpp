#include "objParser.h"

#include <fstream>
#include <stdexcept>
#include <sstream>

void parseFile(std::string name, std::vector<float>& outVect) {
    std::ifstream objFile;
    objFile.open("../data/" + name);
    if (!objFile.is_open()) {
        //throw an error
        throw std::invalid_argument("File \"" + name + "\" cannot be opened");
    }

    std::string line;

    std::vector<glm::vec3> verticies;
    //std::vector<glm::vec2> uvs;
    //std::vector<glm::vec3> normals;
    std::vector<std::vector<int>> faces;
    
    while (getline(objFile, line)) {
        std::istringstream lineStream(line);

        //each line SHOULD start with a string describing whats on the line
        std::string lineHeader;
        lineStream >> lineHeader;
        
        //verticies eg "v -1.000000 -1.000000 1.000000"
        if (lineHeader == "v") {
            glm::vec3 v;
            lineStream >> v.x >> v.y >> v.z;
            verticies.push_back(v * glm::vec3(0.5f, 0.5f, 0.5f));
        }
        /*
        //vertex textures eg "vt -1.000000 -1.000000 1.000000"
        else if (lineHeader == "vt") {
            glm::vec2 uv;
            lineStream >> uv.x >> uv.y;
            uvs.push_back(uv);
        }
        //vertex normals eg "vn -1.000000 -1.000000 1.000000"
        else if (lineHeader == "vn") {
            glm::vec3 normal;
            lineStream >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        */
        //faces eg "f 4//4 3//3 2//2 1//1 ..." or "f 4/4/4 3/3/3 2/2/2 1/1/1 ..."
        else if (lineHeader == "f") {
            std::vector<int> face;
            std::string faceIndex;
            while (lineStream >> faceIndex) {
                //push back the first int in this string before the /
                face.push_back(std::stoi(faceIndex.substr(0, faceIndex.find('/'))) - 1);
            }
            faces.push_back(face);
        }
    }
    

    //now process the verticies by faces 
    for (auto face : faces) {
        for (unsigned int i = 0; i < face.size()-2; i++) {
            for (unsigned int j = 0; j < 3; j++){
                glm::vec3 v = verticies[i+j];
                outVect.push_back(v.x);
                outVect.push_back(v.y);
                outVect.push_back(v.z);
                for (unsigned int k = 0; k < 3; k++) {
                    if (k == j) {
                        outVect.push_back(1.0f);
                    }
                    else {
                        outVect.push_back(0.0f);
                    }
                }
            }
        }
    }
    return;
};
