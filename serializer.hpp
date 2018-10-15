#include <string>
#include <vector>

class Serializer {
private:
    const Solution &solution_;

/*    template<typename A, typename B>
    std::pair <B, A> flip_pair(const std::pair <A, B> &p) {
        return std::pair<B, A>(p.second, p.first);
    }

    template<typename A, typename B>
    std::multimap <B, A> flip_map(const std::map <A, B> &src) {
        std::multimap <B, A> dest;
        std::transform(
                src.begin(),
                src.end(),
                std::inserter(dest, dest.begin()),
                flip_pair<A, B>);
//                [](const std::pair x) { return std::pair(x.second, x.first))});
        return dest;
    }*/

    template<typename A, typename B>
    std::pair <B, A> flip_pair(const std::pair <A, B> &p) {
        return std::pair<B, A>(p.second, p.first);
    }

    template<typename A, typename B>
    std::multimap <B, A> flip_map(const std::map <A, B> &src) {
        std::multimap <B, A> dst;
        std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                       flip_pair<A, B>);
        return dst;
    }

public:
    Serializer(Solution &solution) : solution_(solution) {
        std::string result;
        auto hours_teachers = solution.get_schedule();
        solution.print_timetable();

        for (auto const &teacher : hours_teachers) {
            auto teacher_id = teacher.first;
            auto schedule = teacher.second;

            std::vector <std::pair<int, int>> pairs;
            for (auto itr = schedule.begin(); itr != schedule.end(); ++itr)
                pairs.push_back(*itr);

            sort(pairs.begin(), pairs.end(), [=](std::pair<int, int> &a, std::pair<int, int> &b) {
                     return a.second < b.second;
                 }
            );

            int last = 0;
            for (const auto & pair : pairs) {
                int student_id = pair.first;
                int time = pair.second;

                for(int i = last + 1; i < time; i++)
                    result += "-";
                for(int i = 0; i < durations[teacher_id]; i++) {
                    result += std::to_string(student_id);
                    last = time + durations[teacher_id];
                }
            }
            result += "\n";
        }

        std::cout << result << std::endl;
    }
};