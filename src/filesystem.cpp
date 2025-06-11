#include <filesystem>
#include <iostream>

auto main(int argc, const char** argv) -> int {
    namespace fs = std::filesystem;

    fs::path path{"."};  // Current directory from where the program is run
    if (argc > 1) {
        path = argv[1];
        std::cout << "Path provided: " << path << "\n";
    } else {
        std::cout << "No path provided, using current directory.\n";
    }
    // Check if a path exists
    if (fs::exists(path)) {
        std::cout << "Path exists: " << path << "\n";
    } else {
        std::cout << "Path does not exist: " << path << "\n";
    }

    std::cout << "Now in: " << fs::current_path() << "\n";

    // Check if it's a directory
    if (fs::is_directory(path)) {
        std::cout << path << " is a directory.\n";
    } else {
        std::cout << path << " is not a directory.\n";
    }

    // Iterate through the directory (Top level)
    if (fs::is_directory(path)) {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_symlink()) {
                std::cout << "Symlink: " << fs::absolute(entry.path()) << "\n";
            } else if (entry.is_regular_file()) {
                std::cout << "File: " << entry.path().lexically_relative("./src") << "\n";
            } else if (entry.is_directory()) {
                std::cout << "Dir:  " << entry.path() << "\n";
            }
        }
    }
    // fs::create_directories("dst/test");
    fs::copy("./src", "dst", fs::copy_options::recursive | fs::copy_options::skip_existing);
    fs::path p = "config/cache/data.db";
    fs::path r1 = fs::absolute(p);
    fs::path r2 = fs::weakly_canonical(p);

    std::cout << "absolute: " << r1 << "\n";
    std::cout << "weakly_canonical: " << r2 << "\n";
    return 0;
}
