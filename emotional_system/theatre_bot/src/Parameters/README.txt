The JSON's tags for each parameters are as follows:

---------------------------------------------------------------------
"name" : "parameter_amplitude"
"amplitude"	:	[X,Y,Z] (where X, Y and Z are float) (radiands)
---------------------------------------------------------------------
"name" : "parameter_circle"
 "point" :	[X,Y,Z] (where X, Y and Z are float) (millimeters)
 "pose" :	[X,Y,Z,W] (where X, Y, Z and W are float)*
 "radio" : R (float)
---------------------------------------------------------------------
"name" : "parameter_landmark"
 "pose" :	[X,Y,Z,W] (where X, Y, Z and W are float)*
 "landmark_id" : I (int)
 "landmark_type" : "TYPE" TYPE = Person_Landmark | Object_Landmark | Place_Landmark
---------------------------------------------------------------------
"name" : "parameter_point"
 "point" :	[X,Y,Z] (where X, Y and Z are float) (millimeters)
 "pose" :	[X,Y,Z,W] (where X, Y, Z and W are float)*
---------------------------------------------------------------------
"name" : "parameter_speech"
"text" : "PHRASES"
---------------------------------------------------------------------
"name" : "parameter_square"
 "point" :	[X,Y,Z] (where X, Y and Z are float) (millimeters)
 "pose" :	[X,Y,Z,W] (where X, Y, Z and W are float)*
 "delta" : [X,Y] (where X and Y are float) (millimeters)
---------------------------------------------------------------------
"name" : "parameter_time"
"time" : X (where X is float)
"emotional_time": X (where X is float)
"repeat_emotional": "BOOL" BOOL = yes | no
---------------------------------------------------------------------
"name" : "parameter_velocity"
"velocity" : [X,Y,Z] (where X, Y and Z are float)
---------------------------------------------------------------------