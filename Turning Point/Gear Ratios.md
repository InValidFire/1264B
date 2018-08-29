# Gear Ratios
So, due to a *ahem* mechanical difficulty in the manipulator design... we need to figure out how to make one larger gear, spin at the same speed as a small gear.

Gears obey the following rules:
* When the driven gear is smaller than the driving gear, you increase torque at the cost of speed.
* When the driven gear is larger than the driving gear, you increase speed at the cost of torque.

By these rules, our smaller gear would be our limiting factor, setting that motor to max, keeping the other motor lower than the other to compensate for the larger size. How much lower is the question we've got to answer. 

Any notes we can find would be of great help.


Possible solution: Assuming the smaller gear has 12 ticks, and the larger one has 48, that'd be a 1:4 ratio. The larger gear would be traveling 4x the distance of the smaller one. So, all we'd have to do is cut power to 1/4th of the smaller gear's power to avoid the larger gear outrunning the smaller gear. Will be testing this hypothesis tomorrow.
