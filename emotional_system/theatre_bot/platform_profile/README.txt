Each platform has to have their own folder with all the action that it is capable to perform.

Each file describes the maximum and minumum for each action, and the reference distance.

The distance is used to modulate the distance to project the emotion, because it is not the same to do it in a small platform that in big platform

for example:
	move_body should have max and min>=0 velocity 
	move_shoulder min and max angle and velocity
	
If there is not an action specify in the file in is consider not to have the posibility to execute that action.

Thus it will not be send any message to the action node.



