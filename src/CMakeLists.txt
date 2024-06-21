set(CHESS_SOURCES
	ChessLoop.cpp
	SDL_Handler.cpp
	FEN.cpp
)

if (WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SDL2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif (WIN32)

add_executable(${PROJECT_NAME} Main.cpp ${CHESS_SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)
