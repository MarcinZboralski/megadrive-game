Map composition
---------------

Map are done using Tiled : http://www.mapeditor.org/
The .tmx is the main file searched by the compiler, then it requires:
 <map_name>_solid.bmp                   the collision tiles
 <map_name>_plan_a_solid.csv            the plane A collision map, exported from Tiled
 <map_name>_plan_a_graphics.bmp         the plane A graphics tiles
 <map_name>_plan_a_graphics.csv         the plane A graphics map, exported from Tiled
 <map_name>_plan_b_solid.csv            the plane B collision map, exported from Tiled
 <map_name>_plan_b_graphics.bmp         the plane B graphics tiles
 <map_name>_plan_b_graphics.csv         the plane B graphics map, exported from Tiled
