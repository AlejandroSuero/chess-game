# set(CHESS_SOURCES
#     ChessLoop.cpp
#     SDL_Handler.cpp
# )

if (WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif (WIN32)

# add_executable(Chess Main.cpp ${CHESS_SOURCES})
add_executable(${PROJECT_NAME} Main.cpp)

target_link_libraries(${PROJECT_NAME} ${SLD2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
