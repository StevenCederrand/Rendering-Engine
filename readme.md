# 3D rendering engine for the course DV1568.

Task list 
- [x] Deferred Rendering - Steven
> I've completed deferred shading now. It was a very 
tedious technique to implement. But it worked out fine. 
What happens is that we create a framebuffer containing 
3 different output textures. Normal, position and colour
texture. These textures are created within and output 
from the geometrypass shader. The textures are later bound 
and used within the lightpass shader.

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
- [x] Normal Mapping - Steven
>Normal mapping is quite an advanced technique. Most examples of
this technique are implemented on the CPU, in C++ code. 
I implemented this technique in the geometry shader. Because the 
geometry shader takes in all of the data that we need to be able to 
implement normal mapping. By this I mean that we have access to 
vertices, normals and uvs for one triangle. 
Implementing it on the GPU I believe is a create advantage over 
implementing it on the CPU. For performance reasons. 
By implementing it on the GPU we avoid having to issue CPU-GPU calls. We 
won't be taking up as much memory on the CPU because we won't store the 
Tangent/bitangent values in the RAM. We also reduce memory use on the 
GPU by only setting out TBN on triangles that aren't culled by the 
backface culling. 
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


