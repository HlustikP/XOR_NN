include_directories(${PROJECT_SOURCE_DIR}/src/headers)
add_executable(XOR_NN XOR_NN.cpp #main file
              Matrix.cpp NeuralNetwork.cpp pch.cpp)