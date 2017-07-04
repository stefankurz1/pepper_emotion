The possible parameters for the actions are shown in the following table:

	--------------------------------
	|Parameter	|Json Value			|
	--------------------------------
	|Amplitude	|parameter_amplitude|
   +|Circle		|parameter_circle	|
  +!|Landmark	|parameter_landmark	|
   +|Point		|parameter_point	|
	|Speak		|parameter_speech	|
   +|Square		|parameter_square	|
	|Time		|parameter_time		|
	|Velocity	|parameter_velocity	|
	--------------------------------

+This parameters could also be added the option of pose which is given in quaternions.
	If the pose is not given is used the current position
!if the landmark is a person the pose is going to be used in terms of person, regarding if the robot arrived
	to person's back, front or sided 

It is important to remember, that the interpretation of each action is leave to the designer of platforms' controllers.
In the case of triskar_small, I used move_shoulder and oscillate_shoulder to modify the robot's upper part. 
And move_torso and oscillate_torso to bend the upper part. 
The actions so far implemented are shown in the following table:
	
	--------------------------------------------------------------------------------
	|Action				|Description												|
	---------------------------------------------------------------------------------
	|do_nothing			| this action does not do anything for a period of time x.	|
	|					|	* mandatory parameter: parameter_time					|
	|-------------------|-----------------------------------------------------------|
	|move_body			| this action moves the body from the current position to	|
	|					|	the desire position.									|
	|					|	* mandatory parameter: any parameter_point			|
	|					|								-less amplitude				|
	|					|	* optional parameters: any time parameter				|
	|-------------------|-----------------------------------------------------------|
	|oscillate_body		| this action makes oscillate the platform by an x angle	|*Note: this action could be used simultaniously
	|					|	without changhing the robot's position.					|			with move_body
	|					|	* mandatory parameter: parameter_amplitude (radians)	|
	|					|	* optional parameters: any time parameter				|
	|-------------------|-----------------------------------------------------------|
	|move_shoulder		| this action moves the shoulder to a desire position		|
	|					|	* mandatory parameter: parameter_amplitude (radians)	|
	|					|	* optional parameters: any time parameter				|
	|-------------------|-----------------------------------------------------------| 
	|oscillate_shoulder	| this action makes a shoulder oscillate by an x angle		| *Note: this action could be used simultaniously
	|					|	* mandatory parameter: parameter_amplitude (radians)	| 			with move_shoulder
	|					|	* optional parameters: any time parameter				|
	|-------------------|-----------------------------------------------------------|
	|move_torso			| this action moves the torso to a desire position			|
	|					|	* mandatory parameter: parameter_amplitude (radians)	|
	|					|	* optional parameters: any time parameter				|
	|-------------------|-----------------------------------------------------------|
	|oscillate_torso	| this action makes a torso oscillate by an x angle			|
	|					|	* mandatory parameter: parameter_amplitude (radians)	|
	|					|	* optional parameters: any time parameter				|
	|-------------------|-----------------------------------------------------------|
	|walk				| it integrates a torso position, shoulder oscillation, and	|
	|					|	point in the space to generate the effect of walking	|
	|					|	* mandatory parameters: -any position parameter			|
	|					|								-less amplitude				|
	|					|							-parameter_amplitude_shoulder	|
	|					|							-parameter_amplitude_torso		|
	|					|	* optional parameters: any time parameter				|
	|-------------------|-----------------------------------------------------------|
	|speak				| it pronouns an speech										|
	|					|	* mandatory parameter: parameter_speech					|
	--------------------------------------------------------------------------------