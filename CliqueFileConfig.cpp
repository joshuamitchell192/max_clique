class CliqueFileConfig {
    public:
    int graphSize;
    int maxCliqueSize;
    CliqueFileConfig();
};

CliqueFileConfig::CliqueFileConfig()
{
    graphSize = 0;
    maxCliqueSize = 0;
}