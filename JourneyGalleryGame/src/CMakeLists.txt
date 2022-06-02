
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}  "Player.h" "Player.cpp" "Game.h" "WallPiece.h" "MyContactListener.h" "InteractableObject.cpp" "MyContactListener.cpp" "Excavation.h" "Case.h" "Table.h" "Wall.h")
target_include_directories(src PUBLIC ./)

target_link_libraries(src PUBLIC pugixml sfml-graphics box2d)
