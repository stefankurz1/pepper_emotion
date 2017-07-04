///////////////////////////////////////////////////////////
//  EmotionalLoad.cpp
//  Implementation of the Class EmotionalLoad
//  Created on:      04-dic-2014 04:42:19 p.m.
//  Original author: julian
///////////////////////////////////////////////////////////

#include "EmotionalLoad.h"

EmotionalLoad::EmotionalLoad() {
}

EmotionalLoad::~EmotionalLoad() {

}

void EmotionalLoad::LoadInformation() {
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	string file, type_of_parameter;
	struct dirent *ent;
	DIR *dir = opendir(directory_path.c_str());
	EmotionParameter *emotion_parameter_temp;
	ActionChanges *action_changes_temp;
	EmotionProfile *emotion_profile_temp;
	if (dir != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (has_suffix(ent->d_name, ".json")) {
				file = directory_path + "/" + ent->d_name;
				std::ifstream test(file.c_str(), std::ifstream::binary);
				if (test.good()) {
					Json::Value tempValue, actionsValue, actionValue,
							parameterValue, parameterValueSpecific;
					bool parsingSuccessful = reader.parse(test, root, false);
					if (!parsingSuccessful) {
						//Include error messages
						std::cout << "Error" << std::endl;
						break;
					}
#ifdef DEBUG_C_PLUS_PLUS
					std::cout << "File:" << file << std::endl;
#endif
					//This gets the whole information in the first level
					vector<string> alias = root.getMemberNames();
					for (vector<string>::iterator iterator_alias =
							alias.begin(); iterator_alias != alias.end();
							iterator_alias++) {
#ifdef DEBUG_C_PLUS_PLUS
						std::cout << *iterator_alias << std::endl;
#endif
						//Get the object of information for the first name
						tempValue = root[(*iterator_alias)];
						//If the value that got it is an object, which are the actions description
						if (tempValue.isObject()) {
							//Get the object description which contains emotionProfileAction, emotionProfileEmotion, type, reference, repetition
							actionsValue = tempValue.get("description",
									"UTF-8");
							emotion_profile_temp = new EmotionProfile;
							if (!actionsValue.isNull()) {
								emotion_profile_temp->setEmotionProfileAction(
										actionsValue.get("emotionProfileAction",
												"UTF-8").asString());
								emotion_profile_temp->setEmotionProfileEmotion(
										actionsValue.get(
												"emotionProfileEmotion",
												"UTF-8").asString());
								emotion_profile_temp->setEmotionProfileName(
										actionsValue.get(
												"emotionProfileEmotion",
												"UTF-8").asString() + "_"
												+ actionsValue.get(
														"emotionProfileAction",
														"UTF-8").asString());
								emotion_profile_temp->setTypeActionEmotion(
										this->getEmotionType(
												actionsValue.get("type",
														"UTF-8").asString()));
							}
							//Get the actions that should be add the emotional values
							actionsValue = tempValue.get("actions", "UTF-8");
							if (!actionsValue.isNull()) {
								vector<string> alias_actions =
										actionsValue.getMemberNames();
								for (vector<string>::iterator iterator_alias_actions =
										alias_actions.begin();
										iterator_alias_actions
												!= alias_actions.end();
										iterator_alias_actions++) {
									action_changes_temp = new ActionChanges;
									action_changes_temp->setActionThatModyfies(
											(*iterator_alias_actions));
									actionValue = actionsValue.get(
											(*iterator_alias_actions), "UTF-8");
									action_changes_temp->setReference(actionValue.get("reference", "UTF-8").asFloat());
									action_changes_temp->setRepetition((actionValue.get("repetition", "UTF-8").asString().compare("yes") == 0) ? true : false);
									Json::Value emotion_values = actionValue.get("parameters", "UTF-8");
									for (unsigned int i = 0;
											i < emotion_values.size(); i++) {
										parameterValue = emotion_values.get(i,
												"UTF-8");
										if(parameterValue.isArray()){
											//First X, Second Y and Third Z
											for (unsigned int j = 0;
												j < parameterValue.size(); j++) {
													parameterValueSpecific = parameterValue.get(j,
														"UTF-8");
													emotion_parameter_temp = this->generateEmotionParameter(
															parameterValueSpecific,
														emotion_profile_temp->getTypeActionEmotion());
												if(i==0){//X
													//If the parameter exist add to the structure
													if (emotion_parameter_temp != 0) {
														action_changes_temp->addEmotionParameter(emotion_parameter_temp);
													}
												}else if(i==1){//Y
													//If the parameter exist add to the structure
													if (emotion_parameter_temp != 0) {
														action_changes_temp->addEmotionParameterY(emotion_parameter_temp);
													}
												}else if(i==2){//Z
													//If the parameter exist add to the structure
													if (emotion_parameter_temp != 0) {
														action_changes_temp->addEmotionParameterZ(emotion_parameter_temp);
													}
												}
											}
										}else{
												emotion_parameter_temp = this->generateEmotionParameter(
														parameterValue,
														emotion_profile_temp->getTypeActionEmotion());
												//If the parameter exist add to the structure
												if (emotion_parameter_temp != 0) {
													action_changes_temp->addEmotionParameter(emotion_parameter_temp);
												}
										}
									}
									emotion_profile_temp->addActionChanges(
											action_changes_temp);
								}
							}
#ifdef DEBUG_C_PLUS_PLUS
							std::cout<<"Adding: "<<emotion_profile_temp->getEmotionProfileName()<<std::endl;
#endif
							emotions_available[emotion_profile_temp->getEmotionProfileName()] =
									emotion_profile_temp;
						}
					}
				}
			}
		}
	}
	closedir(dir);
}

std::map<string, EmotionProfile *> EmotionalLoad::getEmotionsAvailable() {
	return emotions_available;
}

EmotionParameter* EmotionalLoad::generateEmotionParameter(Json::Value info,
		EmotionType type_emotion) {
	if (type_emotion == MovementParameter) {
		EmotionMovementParameter * parameter_temp = new EmotionMovementParameter;
		parameter_temp->setEmotionParameterTime(info.get("time","UTF-8").asFloat());
		parameter_temp->setEmotionParameterSpacing(info.get("space","UTF-8").asFloat());
		return parameter_temp;
	}
	return 0;
}

EmotionType EmotionalLoad::getEmotionType(std::string emotion_type) {
	if (emotion_type.compare("movement_parameter") == 0)
		return MovementParameter;
	return UnknownEmotionType;
}

bool EmotionalLoad::has_suffix(const string& s, const string& suffix) {
	return (s.size() >= suffix.size())
			&& equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}
