class LRUCache {
public:
    // intialise with capacity
    LRUCache(int capacity) : _capacity(capacity) {}

    // get key value if exists, return -1 if not
    int get(int key) {
        if (_pairs.find(key) == _pairs.end()) {
            return -1;
        }
        _update_lru_keys(key);
        return _pairs[key].first;
    }

    // update key value if exists, add to the map if not
    void put(int key, int value) {
        // create if not exists, update if alreday exists
        if (_pairs.find(key) == _pairs.end()) {
            _lru_keys.push_front(key);
            _pairs[key] = std::make_pair(value, _lru_keys.begin());
            if (_pairs.size() == (_capacity + 1)) {
                // let's drop the least recently used key from the pairs
                // because it exceeds the capacity.
                _drop_lru_key();
            }
        } else {
            _pairs[key].first = value;
            _update_lru_keys(key);
        }
    }

private:
    void _drop_lru_key() {
        int key = _lru_keys.back();
        _lru_keys.pop_back();
        _pairs.erase(key);
    }

    // update lru_keys
    // example: with capacity = 2
    // put 2 -- 2 
    // put 1 -- 1 <- 2
    // put 3 -- 3 <- 1
    // get 1 -- 1 <- 3
    void _update_lru_keys(int key) {
        std::list<int>::const_iterator it = _pairs[key].second;
        _lru_keys.splice(_lru_keys.begin(), _lru_keys, it);
    }

private:
    int _capacity{0};
    // key -> value, const list iterator-destination of the element
    // we use map here in order to ensure O(1) when inserting, deleting or accessing
    // to the elements.
    std::unordered_map<int, std::pair<int, std::list<int>::const_iterator>> _pairs;

    // update after each access, eitehr put or get
    // we use list here.
    // we could've used std::deque (double ended queue), also supports front-back access
    // however, it holds contiguous memory blocks, which means elements must be shifted 
    // when we erase a middle element to move it to the front, all other iterators will
    // be invalidated.
    // while list memory is not contiguous, scattered instead. Once we know the iterator
    // we can move it to wherever we want without invalidating others.
    // std::list will re-order pointers instead moving/copying the data itself.
    std::list<int> _lru_keys;

};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
