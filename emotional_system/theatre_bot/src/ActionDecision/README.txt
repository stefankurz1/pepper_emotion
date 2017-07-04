The action decision read a file script.json

Each node has its own 

The structure of this file is the following (be aware that this example includes comments taht should be deleted in a real json file):
{
	"initial_beat"	:	id, -> id is a number
	"final_beats"	:	[ids], where ids is a list of number delimited by comma 
	"panic_beats"	:	[ids], where ids is a list of number delimited by comma
	"beats"			:
		[
			{
				"id"			:	number,
				"conditions"	:	conditions, a conditin should be 
				"successors"	:	
					{
						"ideal" 		:	number,
						"alternatives"	:	
						[
							{
								"id"			:	number,
								"desirability"	:	number
							}
						]
					}
				
			}
		]
}

