#include <vector>
#include <string>

const char *dajStranicu(std::vector<int> &vrijeme, std::vector<int> &napon){
    const char *prvi_dio = "<!DOCTYPE html>\n"
                        "<html>\n"
                        "<head>\n"
                        "<title>Function Graph</title>\n"
                        "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>\n"
                        "</head>\n"
                        "<body>\n"
                        "<canvas id=\"myChart\"></canvas>\n"
                        "<script>\n"
                        "var data = [];\n";

    std::string s;

    s+=prvi_dio;

    for(int i = 0; i<vrijeme.size(); ++i){
        s += "data.push({ x:";
        s += std::to_string(vrijeme[i]);
        s+= ", y: ";
        s+= std::to_string(2 * napon[i] * 3.3/4095);
        s+= " });\n";

    }

    s += "var ctx = document.getElementById(\'myChart\').getContext(\'2d\');\n"
                        "var chart = new Chart(ctx, {\n"
                        "type: \'line\',\n"
                        "data: {\n"
                        "datasets: [{\n"
                        "label: \'Function Graph\', data: data,\n"
                        "backgroundColor:\'rgba(75,192,192,0.2)\',\n"
                        "borderColor:\'rgba(75,192,192,1)\',\n"
                        "borderWidth:1\n"
                        "}]\n"
                        "},\n"
                        "options: {\n"
                        "scales: {x:{type:\'linear\',position:\'bottom\'}}}\n"
                        "});\n"
                        "</script>\n"
                        "</body>\n"
                        "</html>";

                        return s.c_str();
                   
}