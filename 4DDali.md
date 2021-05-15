# Solution to the 4D equivalent of the Dali cross

How to tile 3D space using the Dali Cross has already been shown [here](https://arxiv.org/pdf/1512.02086.pdf). With the 4D equivalent I'm referring to the 3D version where the block covered on all sides in 3D has an additional block attached each side along the fourth dimension.

## Notes on the visiualisation

Like many solution on [WHUTS](https://whuts.org/), I too have used [Minecraft](https://www.minecraft.net) for quikly building block structures in 3D. To visualize 4D shapes we will need to look at different cuts for the 4D tiling. In the following images concerete and wool was used for the crosses and glass serves as a marker for intentional gaps. We will first tile 3D space using the regular 3D Dali cross while leaving some gaps. At the same time we will look at what effect this has one unit along the fourth dimension. And finally we will look at how we can combine the 3D tilings with gaps and blocks sticking out to tile 4D space.

Note that this explanaition has the y and z axis swapped compared to Minecrafts coordinate system and instead tries to match the code for validating this tiling.

## Explanaition

We start by putting dali crosses along the x-axis, pointing in opposite directions. We additionally add in some indicators (glass) for holes above and below. Two holes for each cross as each cross has two more blocks which are not part of the current cut.

![Step1A](/images/4DDali_Step1_A.png)

If we look at what happens one unit forward or backwards on the w-axis we will get a pattern like this.
Note that the glass blocks indicate the locations of the holes in our initial 3D tiling just one unit moved on the w-axis.
Note that moving two blocks along the x-Axis left or right and one block up or down on the z-Axis will line each a block up with an indactor of a hole.

![Step1B](/images/4DDali_Step1_B.png)

We will now stick our previos shape together to fill a plane.
We only need to translate our structure in 3D space, no rotations required.

![Step2A](/images/4DDali_Step2_A.png)

Looking one unit over on the w-Axis this is the effect we get.
The property of how the holes lining up is still true.

![Step2B](/images/4DDali_Step2_B.png)

We can now stack these previos stuctures by only translating them in 3D space.
This way we have filled up an entire 3D volume except for the holes we left intentionally and with some blocks sticking out in to the fourth dimension.
This screenshot was taken from the opposite side compared to the previous two as this makes it more obvious how the unfoldings are stacked.

![Step3A](/images/4DDali_Step3_A.png)

Finally this is the shape of the blocks sticking out one unit over on the w-axis. However due the property of how the holes are located.
We can easily take another such 3 tiling to line it up with half the holes.
While the blocks sticking out of the previous volume will fit in half the holes of the holes of the new volume.
So we simply take a copy shift it one unit forward on the w-axis two units forward on the x-axis and one unit up on the z-axis.
We can repeat this process to tile the entire four dimensional space.
The other half of the holes is then always covered by the volume one unit backwards one the w-axis, which has blocks sticking out two units backwards on the x-axis and one unit down the z-axis.

![Step3B](/images/4DDali_Step3_B.png)

The test for validating that this work can be found [here](/src/4D_Dali.cpp)!
Which will fill up a 4 by 20 by 20 by 20 grid using 3200 four dimensional crosses.
