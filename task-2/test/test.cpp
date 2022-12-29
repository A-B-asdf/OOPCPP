#include <iostream>
#include <set>
#include "test_main.cpp"

TEST(main_test, test1) {
    //////////////////////// ARRANGE ////////////////////////
    int iterations = 4;
    std::string input_file = "Glider.txt";
    std::string output_file = "asdf.txt";
    mode_type mode = OFFLINE;
    CmdArgs args = CmdArgs(iterations, 
                           input_file, 
                           output_file, 
                           mode);
    UniverseParser parser = UniverseParser(args);
    Universe universe = Universe();
    std::pair<int, int> size = {10, 10};
    universe.SetSize(size);
    parser.Parse(universe);
    OfflineController controller = OfflineController(universe, args);
    //////////////////////// ACT ////////////////////////
    for (int i = 0; i < 4; ++i) {
        controller.Tick();
    }
    //////////////////////// ASSERT ////////////////////////
    std::string correct_field = 
        ".........."
        ".........."
        ".........."
        ".........."
        ".........."
        ".......*.."
        ".....*.*.."
        "......**.."
        ".........."
        ".........."
    ;
    for (int x = 0; x < size.first; ++x) {
        for (int y = 0; y < size.second; ++y) {
            EXPECT_EQ(universe.IsCellAlive(x, y), correct_field[x * size.first + y] == '*');
        }
    }
}
