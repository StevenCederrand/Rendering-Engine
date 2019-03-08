# 3D rendering engine for the course DV1568.

Task list 
- [x] Deferred Rendering
> What is left is the shading. But that'll be done today, 
then the description for this technique will be added.
- [x] Obj Parsing - Steven 
> I have reworked the parser and now it works well. What 
happens is the following. Initially the Fileloader inserts 
all valid extensions to its extension vector. So everyfile 
that we request to look up, we will check to see if we 
support it. If it's an .obj then we start to read the 
contents of the file. All positions, normals and uv's are 
pushed into their own vector. When interpretting faces we 
pass through a Mesh type. Which contains a vector of 
"Vertex"(a combination of positions, normals and UV's). 
Each face is divided upp in the following structure, 
V/VT/VN. We add all of this data to the mesh. Then all we 
have left is the .mtl file. Which is fairly straight 
forward. We save all relevant data such as colours into 
glm::vec3 etc. 
- [x] Height Map - Ludwig
>I read the all the colour values from the picture and save 
them in a vector. We calculatethe 4 courners (2 triangles) 
where the y value is the value of the colour from our picture. 
Then we add them counterclockwiseto a vertex vector. 
Add the vertex vector to the Mesh and then add the 
mesh to our Object and return the Object.
- [ ] Normal Mapping - Steven
- [ ] Shadow Mapping - Ludwig 
- [x] Front and Back Rendering - Steven
>Front to back rendering is a simple technique to implement. My 
implementation of this technique is straight forward as well. 
Before we issue the draw calls and send the object data to the gpu
we sort the vector of objects based on the quadratic distance to the
camera. That is we take mathematical vector between the camera and 
object[i], take thereafter the dot product between it and itself. 
This will result in the value beneath the root. This is a way to
reduce cumbersome mathematical operations, that are to be handled
by the CPU. 
- [x] Back Face Culling in GS - Steven 
>This was a very simple problem to be honest. What I did to solve this 
was to send 3 vertices to the geometry shader. Then I took the normal 
for these two points. Then check to see that the dot product between 
the cameratovertex([i]) and the normal is > 0. If it is then we render 
the emit the vertex/primitive. Otherwise we skip emitting the 
primitive. NOTE! Although this is marked as done there is a weird glitch 
with the floor. Which has to be solved before we show this to Francisco!
- [ ] Billboarded Particles - Steven
- [ ] Glow Effect - Ludwig



2019-01-03
> The project is setup as a base right now, what has been implemented is 
just a simple window manager and some other smaller details. 
Currently working on implementing an .obj parser and a simple control 
manager. 


