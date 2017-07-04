action_execution_synch
	* Description: this recieves all the messages for synchronization from all the nodes.
	* The message used is ActionExecutionMessage:
		-string coming_from - the action that generates the message
		-string message - it could be:
									*finish_action - when the action has finish
									*finish_emotion - when the emotion part has finish
									
change_emotion_parameters
	
change_action_parameters
	* Description: this sends the information to all the nodes, so each node has to verify if the information is for them.
		This could be improved dividing one for each node, but it introduces how to manage this locally.
	* The message used is ActionExecutionMessage
		- string coming_from: tells from which actions the message is originated
		- string coming_to: tells to which action are the parameters
		- string message: it has the parameters in JSON format (to see the format of the parameters go to src->Parameters->README.txt)
		- bool stop_action: tells if the action should stop
		
change_emotion
	* Description: this send the new emotions with intensity
		if the emotion is not find it in all the possibilites is changed to neutral emotion
		if the intensity is 0 all the emotional part is deleted
		
change_action
	* Description: this tells all the action that should be executed. The action could be a very complex actions compoused by diferent action that can be executed in parallel or sequenatiallyy