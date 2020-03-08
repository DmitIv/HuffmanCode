//
// Created by dmitri on 07.03.2020.
//

#include "QueueConnectionHandler.h"
#include "utility.hpp"

int main() {
    using Builder = AMQP::ConnectionBuilder;
    using Connector = AMQP::Connector;
    using Speaker = AMQP::SpeakHandler;

    Connector connector = Builder().Build();
    Speaker speaker = connector.CreateSpeaker(AMQP::SpeakAdapter());

    speaker.Publish(UTILITY::attach_prefix(UTILITY::ON_PROCESSING_PREFIX, UTILITY::PREFIX_DELIMITER,
            "First message: Hello, World!"));
    speaker.Publish(UTILITY::attach_prefix(UTILITY::ON_PROCESSING_PREFIX, UTILITY::PREFIX_DELIMITER,
            "Second message: I'm still alive;)"));
    speaker.Publish(UTILITY::attach_prefix(UTILITY::ON_PROCESSING_PREFIX, UTILITY::PREFIX_DELIMITER,
                "Third message: Tired with all these, for restful death I cry:\n"
                    "As to behold desert a beggar born,\n"
                    "And needy nothing trimmed in jollity,\n"
                    "And purest faith unhappily forsworn,\n"
                    "And gilded honour shamefully misplaced,\n"
                    "And maiden virtue rudely strumpeted,\n"
                    "And right perfection wrongfully disgraced,\n"
                    "And strength by limping sway disabld,\n"
                    "And art made tongue-tied by authority,\n"
                    "And folly (doctor-like) controlling skill,\n"
                    "And simple truth miscalled simplicity,\n"
                    "And captive good attending captain10 ill:\n"
                    "Tired with all these, from these would I be gone,\n"
                    "Save that, to die, I leave my love alone."));
    speaker.Publish(UTILITY::attach_prefix(UTILITY::ON_PROCESSING_PREFIX, UTILITY::PREFIX_DELIMITER,
            "Fourth message: It was Shakespear sonnet"));
    speaker.Publish(UTILITY::attach_prefix(UTILITY::ON_END_PREFIX, UTILITY::PREFIX_DELIMITER, "END"));
}