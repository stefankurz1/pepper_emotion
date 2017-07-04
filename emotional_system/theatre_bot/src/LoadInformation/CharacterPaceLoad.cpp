/*
 * CharacterPaceLoad.cpp
 *
 *  Created on: Dec 18, 2014
 *      Author: julian
 */

#include "CharacterPaceLoad.h"

CharacterPaceLoad::CharacterPaceLoad() {
	// TODO Auto-generated constructor stub

}

CharacterPaceLoad::~CharacterPaceLoad() {
	// TODO Auto-generated destructor stub
}

void CharacterPaceLoad::LoadInformation(){
	std::string file;
	struct dirent *ent;
	DIR *dir = opendir(directory_path.c_str());
	if (dir != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (has_suffix(ent->d_name, ".json")) {
				file = directory_path + "/" + ent->d_name;
				this->LoadSpecificInformation(file);
			}
		}
	}
	closedir(dir);
}

void CharacterPaceLoad::LoadSpecificInformation(std::string file){
	std::ifstream test(file.c_str(), std::ifstream::binary);
	Json::Value root;
	Json::Reader reader;
	if (test.good()) {
		bool parsingSuccessful = reader.parse(test, root, false);
		if (!parsingSuccessful) {
			//Include error messages
			std::cout << "Error" << std::endl;
			return;
		}
		CharacterEmotionModification *temp_character_emotion = new CharacterEmotionModification;
		temp_character_emotion->setEmotionName(root.get("emotion","UTF-8").asString());
		Json::Value actions = root.get("actions","UTF-8");
		Json::Value value;
		for (unsigned int i = 0; i < actions.size(); i++) {
			CharacterMovementModification * temp_character_movement = new CharacterMovementModification;
			value = actions.get(i,"UTF-8");
			temp_character_movement->setActionName(value.get("action","UTF-8").asString());
			temp_character_movement->setAmplitude(value.get("amplitude","UTF-8").asFloat());
			temp_character_movement->setBias(value.get("bias","UTF-8").asFloat());
			temp_character_movement->setLongness(value.get("logness","UTF-8").asFloat());
			temp_character_emotion->addParameter(temp_character_movement);
		}
		character_emotion_information[temp_character_emotion->getEmotionName()] = temp_character_emotion;
	}
}


std::map<std::string, CharacterEmotionModification *> CharacterPaceLoad::getCharacterMovementInformation(){
	return this->character_emotion_information;
}
