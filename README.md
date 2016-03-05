#Height Calibrator

###Description

Height calibrator allows you to get the object's height on the scene with the help of anchor posts.
Anchor post is the post on the scene with known height (scene-space). At least 3 posts are required.

###Algorithm

1. Initialization
  1. Find intersection point for the line that connects posts' bottoms and the line that connects posts' tops. Do it each to each post. As a result we have a vector of intersection points.
  2. Find the skyline via the Least Squares method.
2. Usage
  1. Find the furthest post from the test post. Count only y-coordinate distance that we assume as the scene depth (it's incorrect but that is all the information we have).
  2. Build line that connects the test post bottom and the furthest post bottom. Find the intersection point with the skyline.
  3. Calculate the required height via the triangle similarity


Anton Egorov, 2016
dohxehapo@gmail.com
