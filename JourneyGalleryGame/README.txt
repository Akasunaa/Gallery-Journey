Ce projet contient un test de Tmxlite (https://github.com/fallahn/tmxlite) avec SFML.

src/myMain.cpp est une adaptation du main.cpp présent dans tmxlite/SFMLExample/src :
- #include "SFMLOrthogonalLayer.hpp"
  est devenu
  include "SFMLOrthogonalLayer.h"
- int main()
  est devenu
  int myMain()
- map.load("assets/demo.tmx");
  est devenu
  map.load("resources/demo.tmx");

src/SFMLOrthogonalLayer.h est la version renommée en .h de SFMLOrthogonalLayer.hpp présent
dans tmxlite/SFMLExample/src

Le répertoire resources contient tout le contenu du répertoire tmxlite/SFMLExample/assets.
