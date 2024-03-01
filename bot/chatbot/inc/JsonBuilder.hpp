#ifndef JSONBUILDER_H
# define JSONBUILDER_H

# include <string>
# include <sstream>


class JsonBuilder {

    public:
        std::string getCompletionJson(const std::string& nickname, const std::string& channel, const std::string& message);
};

#endif
