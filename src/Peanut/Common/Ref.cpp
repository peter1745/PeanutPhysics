#include <unordered_set>
#include <mutex>

namespace Peanut {

	static std::unordered_set<void*> s_LiveReferences;
	static std::mutex s_LiveReferenceMutex;

	namespace RefUtils {

		void AddToLiveReferences(void* instance)
		{
			std::scoped_lock<std::mutex> lock(s_LiveReferenceMutex);
			s_LiveReferences.insert(instance);
		}

		void RemoveFromLiveReferences(void* instance)
		{
			std::scoped_lock<std::mutex> lock(s_LiveReferenceMutex);
			if (s_LiveReferences.find(instance) == s_LiveReferences.end())
				return;
			s_LiveReferences.erase(instance);
		}

		bool IsLive(void* instance)
		{
			return s_LiveReferences.find(instance) != s_LiveReferences.end();
		}
	}


}
