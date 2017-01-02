struct attribute_map {
    using Key   = std::string;
    using Value = std::string;

    template <typename ... Args>
    attribute_map (Args && ... args) {
        insert(args...);
    }

    template <typename ... Args>
    void insert (Key const & attribute, Value const & value, Args && ... args) {
        static_assert(sizeof...(Args) % 2 == 0, "invalid key/value pairings");
        insert(attribute, value);
        insert(args...);
    }

    void insert (Key const & attribute, Value const & value) {
        std::cout << "\t" << attribute << " -> " << value << std::endl;
        // TODO - something more interesting
    }
};

struct node {
    template <typename ... Args, typename std::enable_if<sizeof...(Args) >= 2, int>::type = 0>
    void apply (std::string const & path, Args && ... args) {
        apply(path, attribute_map { args ... });
    }

    void apply (std::string const & path, attribute_map const & attributes) {
        std::cout << path << std::endl;
        std::cout << "\t---> apply attributes" << std::endl;
    }
};

int main () {
    attribute_map map = { "a", "apple", "b", "banana", "c", "cabbage" };

    node node;
    node.apply("path.to.node", "a", "apple", "b", "banana", "c", "cabbage");
    node.apply("path.to.node", map);
}
