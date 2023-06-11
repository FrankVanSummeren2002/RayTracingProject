-------------------switching scenes
in source.cpp is a switch case with multiple different
switch cases. in source there is a const int named scene. Case 3 to 7 are from the weekly assignment.
every other value goes to default which gets a random image.
-----------------------------------


-------------------bugs
-there seems to be an issue with the screen rotation once you rotate to much
-there seems to be an issue with the edge of the object array
if you try greating a scene with max amount of objects the screen gets corupted.
- there seems to be an issue with the rotated box inside the BVH where if you look
at it from certain angles it disapears.
- the unit test seems to sometimes have an issue with the cmath which causes it to not be able to run
-----------------------


------------------movement and rotation
the controls for movement and rotation are
-WASD for movement
-QE to roll
-ARROW UP/DOWN for pitch
-ARROW LEFT/RIGHT yaw
-Hold SHIFT to increase speed of rotation and movement
---------------------------------------


-----------------Adding lights
To add point lights go to source.cpp and type objectmanager.AddPointLight(new lightsource(vec3 location, vec3 color, float brightness))
To add Area lights go to source.cpp and type objectmanager.AddAreaLight(new AreaLight(shape), float brightness), bool to use the BVH);
------------------------------



-----------------Adding Shapes--------------------
to add a shape you will have to go into source.cpp and type objectmanager.AddShape(shape,bool use the BVH or not)

-----------------ADDING planes and quads
Planes and quads both fall under the same class named plane.
The plane can be constructed in two different ways either with 3 points or one point and a normal.
then the plane needs a color and a material After that comes a boolean for the checkerboard pattern and a second color that is used for the checkerboard.
then you have the following options: Absorbsion only used for refractions and reflections, a second material, a float to give the percentage of the first material.
if you want to make it a quad you can also pass 3 floats at the end to give size of the quad. 
----------------------------------------

-----------------Adding Boxes
the box first takes three floats in its constructor a width,height and depth then a vec3 for its center. Then a color the base color and then a base color. 
Then there are some options you can give. First you can give an absorbtion then there are 3 floats for rotation around the x, y ,z axis. 
After that we have a boolean for multiple colors the base color becomes the color for the sides that originaly started on the x-axis, after the boolean you
can place 2 more vectors for the colors for the other planes. After this you can add a second material and a percentage of how strong the first material is
-----------------------------

-----------------Adding Spheres
to add spheres you start with the radius and then the center, color and material. 
If you want you can add an vector for absorbtion, a second material and a float for the stength of the first material 

-------------------------------
--------------------------------------------------
