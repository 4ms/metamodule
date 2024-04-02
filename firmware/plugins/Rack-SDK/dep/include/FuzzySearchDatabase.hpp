#pragma once

#ifndef FUZZY_SEARCH_DATABASE_HPP
#define FUZZY_SEARCH_DATABASE_HPP

// Copyright 2022 Nils Jonas Norberg <jnorberg@gmail.com>
// license: BSD-3-Clause ( https://opensource.org/licenses/BSD-3-Clause )

// updates, requests, comments:
// https://bitbucket.org/j_norberg/fuzzysearchdatabase

// The main levers are:

// 1. How to score a partial match (scoreQueryWordToWord)
//   a. If length is similar use a levenshtein distance as base, and some bonus if common prefix or suffix
//   b. If query is substring, bonus if at beginning or end
//   c. If word is substring of word, penalty compared to case b. above

// 2. How to add multiple matches (scoreEntry)
//   a. Best score + scaled-down-Soft-clipped sum (to not over-power perfect match)
//   b. An entry with fewer words should win over a similar quality match with more words. Search: "multiWordPenalty"

// 3. How to handle multiple query-words (scoreEveryEntry)
//   a. for each entry, multiply the score for each query-word ()
//   b. prefer consecutive matches... search "TempResultOrderPenalty& penalty = _tempResultsOrderPenalty[i];"

// 4. (User) How to set the weights

#ifdef _MSC_VER // compiles with /Wall in VS
#pragma warning(push)
#pragma warning(disable : 4267)
#pragma warning(disable : 4365)
#pragma warning(disable : 4514)
#pragma warning(disable : 4571)
#pragma warning(disable : 4625)
#pragma warning(disable : 4626)
#pragma warning(disable : 4710)
#pragma warning(disable : 4774)
#pragma warning(disable : 4820)
#pragma warning(disable : 5026)
#pragma warning(disable : 5027)
#pragma warning(disable : 5045)
#endif

#include <vector>
#include <unordered_map>
#include <string>
#include <cctype>
#include <cstring>
#include <algorithm>

#ifdef _MSC_VER
#pragma warning(pop) 
#endif

#ifdef _MSC_VER // compiles with /Wall in VS
#pragma warning(push)
#pragma warning(disable : 4820) // ignore warning: padding inserted
#pragma warning(disable : 5045) // ignore warning: specre mitigation (if /Qspectre specified)
#endif

namespace fuzzysearch
{

	// helper class for the fuzzy distance
	class HelperFunctions
	{
		static inline int min3(int a, int b, int c)
		{
			return (a < b) ? (a < c ? a : c) : (b < c ? b : c);
		}

		// 
		static inline int substringFind(const char* queryWord, size_t queryLength, const char* w, size_t limit)
		{
			for (size_t i = 0; i <= limit; ++i)
			{
				if (0 == memcmp(w + i, queryWord, queryLength))
				{
					return (int)i;
				}
			}

			return -1;
		}

		static inline float substringScore(const char* queryWord, size_t queryLength, const char* wordBegin, size_t wordLength)
		{
			size_t limit = wordLength - queryLength;

			int found = substringFind(queryWord, queryLength, wordBegin, limit);
			if (found < 0)
			{
				return 0.0f;
			}

			// score higher if length of substring is closer to the whole word
			float divisor = 1.0f + (float)limit * 0.02f;

			if (found == 0)
			{
				// first
			}
			else if (found == (int)limit)
			{
				// last
				divisor += 0.02f;
			}
			else
			{
				// middle
				divisor += 0.06f;
			}

			float score = 1.0f / divisor;

#if 0
			// debug-print
			for (size_t i = 0; i < wordLength; ++i)
			{
				putchar(wordBegin[i]);
			}
			printf(" = %f\n", score);
#endif

			return score;
		}

		static inline int levDistance(const char* a, size_t aL, const char* b, size_t bL, int& prefixBonus, int& suffixBonus)
		{
			// ------------------------------------------------------
			// https://en.wikipedia.org/wiki/Levenshtein_distance

			prefixBonus = 0;
			suffixBonus = 0;

			// common prefix
			while (aL > 0 && bL > 0 && a[0] == b[0])
			{
				++a;
				++b;
				--aL;
				--bL;
				++prefixBonus;
			}

			// common suffix
			while (aL > 0 && bL > 0 && a[aL - 1] == b[bL - 1])
			{
				--aL;
				--bL;
				++suffixBonus;
			}

			// simple case
			if (aL < 1) return (int)bL;
			if (bL < 1) return (int)aL;

			enum { kBuf = 16, kLen = kBuf - 1 };

			// clamp length
			if (aL > kLen) aL = kLen;
			if (bL > kLen) bL = kLen;

			// used during distance-calculations
			// currently have a length-limit on words, should be ok
			// this could in theory be just two rows ( or even one )
			int bufDist[kBuf * kBuf];

			size_t stride = aL + 1;

			// init top
			for (size_t x = 0; x <= aL; x++)
				bufDist[x] = (int)x;

			// fill rest of matrix
			for (size_t y = 1; y <= bL; y++)
			{
				size_t index = y * stride + 1;

				// init-left side
				bufDist[index - 1] = (int)y;

				int bChar = b[y - 1];

				// in theory, could unroll this a little-bit
				for (size_t x = 1; x <= aL; ++x, ++index)
				{
					int substitutionCost = (a[x - 1] == bChar) ? 0 : 1;

					int t = min3(
						bufDist[index - 1] + 1,
						bufDist[index - stride] + 1,
						bufDist[index - stride - 1] + substitutionCost
					);

					bufDist[index] = t; // write
				}
			}

			// return
			int dist = bufDist[bL * stride + aL];
			return dist;
		}

		static inline bool isDivider(int c)
		{
			// possible improvement, support utf8
			// maybe this is a bit agressive
			// this will treat every character not mentioned below as a delimiter
			if ('a' <= c && c <= 'z') return false;
			if ('A' <= c && c <= 'Z') return false;
			if ('0' <= c && c <= '9') return false;
			if (c == '+') return false;
			if (c == '-') return false;
			if (c == '&') return false;

			return true;
		}



	public:

		static inline void toLower(std::string& s)
		{
			for (size_t i = 0; i < s.size(); ++i)
				s[i] = (char)std::tolower(s[i]);
		}

		static inline std::vector< std::string > splitString(std::string s)
		{
			std::vector< std::string > ss;

			size_t left = 0;
			size_t right = 0;

			for (; left < s.size(); ++left)
			{
				// 1. skip all dividers
				if (isDivider(s[left]))
					continue;

				right = left + 1;

				// 2. skip all non-dividers 
				for (; right < s.size(); ++right)
					if (isDivider(s[right]))
						break;

				ss.push_back(s.substr(left, right - left));
				left = right;
			}

			return ss;
		}

		// tiny single-bit-histogram
		// early out many words with this
		struct WordHist
		{
			WordHist(std::string s)
			{
				_mask = 0;
				for (size_t i = 0; i < s.size(); ++i)
				{
					int c = s[i];
					_mask |= 1 << charToBit(c);
				}
			}

			static uint32_t charToBit(int c)
			{
				// all numbers collapse to same symbol (31)
				uint32_t b = 31;

				// support 'a' .. 'z'
				if (c >= 'a' && c <= 'z')
					b = (uint32_t)(c - 'a');

				// fixme deal with +/&? (maybe not needed for early-outs)
				return b;
			}

			bool canSkip(WordHist o) const
			{
				uint32_t v = _mask & o._mask;
				return v == 0;
			}

			uint32_t _mask = 0; // one bit per letter
		};

		// tiny word-pair histogram
		struct WordHist2
		{
			WordHist2(std::string s)
			{
				for (int i = 0; i < 32; ++i)
					_followingMask[i] = 0;

				size_t len = s.size();
				uint32_t a = WordHist::charToBit(s[0]);
				for (size_t i = 1; i < len; ++i)
				{
					uint32_t b = WordHist::charToBit(s[i]);
					_followingMask[a] |= 1 << b;
					a = b;
				}
			}

			int countMatchingPairs(const char* s, size_t len) const
			{
				int sum = 0;

				uint32_t a = WordHist::charToBit(s[0]);
				for (size_t i = 1; i < len; ++i)
				{
					uint32_t b = WordHist::charToBit(s[i]);
					uint32_t mask = (uint32_t)(1 << b);
					uint32_t overlap = _followingMask[a] & mask;
					if (overlap != 0)
						++sum;
					a = b;
				}
				return sum;
			}

			uint32_t _followingMask[32];
		};

		// query is expected to be shorter than word 
		static inline float scoreLev(const char* queryBegin, size_t queryLength, const char* wordBegin, size_t wordLength)
		{
			int prefixBonus = 0;
			int suffixBonus = 0;
			float fuzzyDist = (float)levDistance(queryBegin, queryLength, wordBegin, wordLength, prefixBonus, suffixBonus);

			// if dist is very very bad
			if (fuzzyDist >= queryLength)
			{
				// late-out
				return 0;
			}

			if (prefixBonus > 0)
			{
				float prefixBonusMul = 4.0f / (4.0f + prefixBonus * 0.25f);
				fuzzyDist *= prefixBonusMul;
			}

			if (suffixBonus > 0)
			{
				float suffixBonusMul = 4.0f / (4.0f + suffixBonus * 0.125f);
				fuzzyDist *= suffixBonusMul;
			}

			// if the distance is very high ( more than half of the word-length )
			// it's not good enough
			if ((fuzzyDist * 2) > wordLength)
			{
				// not good enough
				return 0;
			}

			float fuzzyDistFrac = (float)fuzzyDist / (float)wordLength;
			float fuzzyScore = 1.0f - fuzzyDistFrac;

			return fuzzyScore;
		}

		static inline float scoreShortQueryWordToWord(const WordHist2& hist, const char* queryBegin, size_t queryLength, const char* wordBegin, size_t wordLength)
		{
			// query is shorter than word

			int matchingPairs = hist.countMatchingPairs(wordBegin, wordLength);
			if ((size_t)(matchingPairs+1) < queryLength)
			{
				// early-out since substring is impossible
				return 0.0f;
			}

			// do we only support actual substring?
			float rawScore = substringScore(queryBegin, queryLength, wordBegin, wordLength);
			return rawScore;
		}

		static inline float scoreLongQueryWordToWord(const WordHist2& hist, const char* queryBegin, size_t queryLength, const char* wordBegin, size_t wordLength)
		{
			if (wordLength < 3)
			{
				// word is short (1 or 2 letters)

				if (wordLength < 2)
				{
					// it's too easy to get bad results for single-character words
					return 0.0f;
				}

				if (queryLength > 5)
				{
					// if the query is much longer... not a good fit
					return 0.0f;
				}
			}

			// query is soo much longer than word
			if (queryLength > wordLength + 8)
			{
				return 0.0f; // don't even worry about it
			}

			int matchingPairs = hist.countMatchingPairs(wordBegin, wordLength);
			if (matchingPairs+1 < (int)wordLength)
			{
				// early-out since substring is impossible
				return 0.0f;
			}

			// so test the other way around (and weigh less)
			// do we only support actual substring?
			float rawScore = substringScore(wordBegin, wordLength, queryBegin, queryLength);
			float otherWayPenalty = 0.7f;

			// adjust even more for very short words (like "and" being a substring of "band")
			if (wordLength < 4)
			{
				otherWayPenalty = 0.6f;
			}

			float adjustedScore = otherWayPenalty * rawScore;
			return adjustedScore;
		}

		// qw - query-Word
		// this gives a score on how well a query-word fits a word
		// 1.0 is a full match
		static inline float scoreQueryWordToWord(const WordHist2& hist, const char* queryBegin, size_t queryLength, const char* wordBegin, size_t wordLength)
		{
			// for very short queries
			if (queryLength <= 3)
			{
				// only accept words of same length or longer
				if (wordLength < queryLength)
				{
					// can not accept backword matching for these
					return 0.0f;
				}

				// for very short queries, only do substrings
				return scoreShortQueryWordToWord(hist, queryBegin, queryLength, wordBegin, wordLength);
			}

			if (queryLength + 3 < wordLength)
			{
				// query is substring (score early substring better)
				return scoreShortQueryWordToWord(hist, queryBegin, queryLength, wordBegin, wordLength);
			}

			if (queryLength > wordLength + 1)
			{
				// word is substring of query (how much longer can a query be?)
				return scoreLongQueryWordToWord(hist, queryBegin, queryLength, wordBegin, wordLength);
			};

			// query is close in length (lev-dist)
			int matchingPairs = hist.countMatchingPairs(wordBegin, wordLength);

			if (matchingPairs + 4 < (int)queryLength)
			{
				// early-out
				return 0.0f;
			}

			if (matchingPairs+1 == (int)queryLength)
			{
				if (queryLength == wordLength)
				{
					// test for 100% match
					if (0 == memcmp(queryBegin, wordBegin, queryLength))
					{
						return 1.0f;
					}
				}
			}

			float score = scoreLev(queryBegin, queryLength, wordBegin, wordLength);
			return score;
		}


	};










	template <typename Key = std::string>
	class Database
	{
	public:

		// ------------------------------------------------------
		// public struct, used for returning the results

		struct Result
		{
			Key key;
			float score;
		};

	private:


		// helper struct to store words close in memory
		struct WordStorage
		{
			std::vector<char> _wordData; // all characters from a word, in order in memory
			std::vector<size_t> _wordEnd; // the "end" marker for each word
			std::vector<HelperFunctions::WordHist> _wordHist; // a tiny histogram per word
			std::unordered_map< std::string, int > _wordMap;

			void clear()
			{
				_wordData.clear();
				_wordEnd.clear();
				_wordHist.clear();
				_wordMap.clear();
			}

			int addWord(std::string word)
			{
				// if exist, return index
				auto found = _wordMap.find(word);
				if (found != _wordMap.end())
				{
					return found->second;
				}

				// add to data
				_wordData.insert(_wordData.end(), word.begin(), word.end());

				// add end-marker
				int wordIndex = (int)_wordEnd.size();
				_wordEnd.push_back(_wordData.size());

				_wordHist.push_back(HelperFunctions::WordHist(word));

				// add to map
				_wordMap.insert({ word, wordIndex });

				// return word-index
				return wordIndex;
			}
		};

		//
		struct WordFromField {
			int _wordIndex; // in global list
			int _fieldIndex;
			int _wordIndexInField; // store some order

			WordFromField(int wIndex, int fIndex, int wordIndexInField)
				: _wordIndex(wIndex)
				, _fieldIndex(fIndex)
				, _wordIndexInField(wordIndexInField)
			{
			}

			bool operator<(const WordFromField& other) const {
				if (_wordIndex != other._wordIndex)
					return _wordIndex < other._wordIndex;

				return _fieldIndex < other._fieldIndex;
			}

			bool operator==(const WordFromField& other) const {
				return
					_wordIndex == other._wordIndex &&
					_fieldIndex == other._fieldIndex;
			}
		};

		// to penalize multi-word queries where the order of hits are reversed
		struct TempResultOrderPenalty
		{
			int _bestIndex = 0;
			int _misses = 0;
		};

		// temporary struct to make sorting smooth
		struct TempResult
		{
			int _entryIndex;
			float _score;

			TempResult()
			{
				set(0.0f, 0);
			}

			TempResult(float score, int entryIndex)
			{
				set(score, entryIndex);
			}

			void set(float score, int entryIndex)
			{
				_score = score;
				_entryIndex = entryIndex;
			}

			bool operator<(const TempResult& other) const {
				return _score > other._score; // reversed to sort high score on top
			}
		};

		// this is the entry, all words are stored in the "WordStorage", only indices here
		struct Entry
		{
			Key _key;
			std::vector<WordFromField> _words;	// index into words from strings
		};


		// ------------------------------------------------------

		// memory-friendly storage for all words
		WordStorage _ws;

		// all entries
		std::vector<Entry> _entries;

		//
		std::vector<float> _fieldWeights;

		//
		float _threshold;

		// "temporary" used during search
		mutable std::vector<float> _scorePerWord;
		mutable std::vector<TempResult> _tempResults;
		mutable std::vector <TempResultOrderPenalty> _tempResultsOrderPenalty;

		static void scoreEveryWord(std::vector<float>& scores, const WordStorage& ws, const std::string& queryWord)
		{
			scores.resize(ws._wordEnd.size());

			const HelperFunctions::WordHist  qHist(queryWord);
			const HelperFunctions::WordHist2 qHist2(queryWord); // calculate fancy letter-pair histogram

			const char* queryBegin = queryWord.c_str();
			const size_t queryLength = queryWord.size();

			// visit every word in memory-order
			size_t wordBeginIndex = 0;
			size_t wordEndSize = ws._wordEnd.size();
			for (size_t i = 0; i < wordEndSize; ++i)
			{
				size_t wordEndIndex = ws._wordEnd[i];

				if (qHist.canSkip(ws._wordHist[i]))
				{
					scores[i] = 0.0f;
				}
				else
				{
					const char* wordBegin = &ws._wordData[wordBeginIndex];
					size_t wordLength = wordEndIndex - wordBeginIndex;
					scores[i] = HelperFunctions::scoreQueryWordToWord(qHist2, queryBegin, queryLength, wordBegin, wordLength);
				}

				// swap to next
				wordBeginIndex = wordEndIndex;
			}
		}

		float scoreEntry(const Entry& e, int& bestIndex) const
		{
			float bestScore = 0;
			float sum = 0;

			size_t wordCount = e._words.size();

			for (size_t ei = 0; ei < wordCount; ++ei)
			{
				const WordFromField& wff = e._words[ei];
				const float localScore = _scorePerWord[(uint32_t)wff._wordIndex];
				if (localScore > 0)
				{
					float weight = _fieldWeights[(uint32_t)wff._fieldIndex];
					float weightedScore = localScore * weight;
					sum += weightedScore;
					if (weightedScore > bestScore)
					{
						bestScore = weightedScore;
						bestIndex = wff._wordIndexInField;
					}
				}
			}

			// skip if nothing good (to avoid log-spam)
			const float epsilon = 0.001f;
			if (sum < epsilon)
			{
				return 0.0f;
			}

			// soft-clip and scale down to never over-power full match
			sum = sum / (1.0f + sum);
			// scale down a bit to make sure one perfect match is higher than a few decent ones
			// can't scale down too much
			sum *= 0.125f;

			float score = bestScore + sum;

			// if we have many words penalize a little bit
			if (wordCount > 1)
			{
				// very very slight penalty (1/200)
				float multiWordPenalty = 1.0f / (1.0f + wordCount * 0.005f);
				score *= multiWordPenalty;
			}

			return score;
		}

		void scoreEveryEntry(size_t pass) const
		{
			if (pass < 1)
			{
				// set
				for (size_t i = 0; i < _tempResults.size(); ++i)
				{
					const Entry& e = _entries[i];
					int bestIndex = 0;
					const float currScore = scoreEntry(e, bestIndex);
					_tempResults[i].set(currScore, (int)i); // also sets the index
					_tempResultsOrderPenalty[i]._bestIndex = bestIndex;
					_tempResultsOrderPenalty[i]._misses = 0;
				}
			}
			else
			{
				const float kEpsilon = 0.001f;

				// multiply
				for (size_t i = 0; i < _tempResults.size(); ++i)
				{
					const Entry& e = _entries[i];
					const float prevScore = _tempResults[i]._score;
					if (prevScore < kEpsilon)
					{
						// no need to even score this entry if it is already filtered out
						continue;
					}

					int bestIndex = 0;
					const float currScore = scoreEntry(e, bestIndex);
					if (currScore < kEpsilon)
					{
						// no need to multiply, also make sure to skip future passes
						_tempResults[i]._score = 0.0f;
						continue;
					}

					TempResultOrderPenalty& penalty = _tempResultsOrderPenalty[i];
					if (bestIndex < penalty._bestIndex)
					{
						++penalty._misses;
						penalty._bestIndex = bestIndex; // score these misses later
					}

					float newScore = prevScore * currScore;
					_tempResults[i]._score = newScore;
				}
			}
		}

	public:


		Database()
		{
			reset();
		}

		void reset()
		{
			_ws.clear();
			_scorePerWord.clear();
			_tempResults.clear();
			_entries.clear();
			_fieldWeights.clear();
			_threshold = 0.1f;
		}

		void addEntry(Key key, const std::vector<std::string>& fields)
		{
			// ensure we have enough weights
			while (_fieldWeights.size() < fields.size())
				_fieldWeights.push_back(1.0f);

			// create entry
			Entry e;
			e._key = key;
			std::vector<WordFromField>& eWs = e._words;

			// iterate fields
			for (size_t fieldIndex = 0; fieldIndex < fields.size(); ++fieldIndex)
			{
				auto words = HelperFunctions::splitString(fields[fieldIndex]);

				// iterate words in this field
				for (size_t wi = 0; wi < words.size(); ++wi)
				{
					std::string& lowerWord = words[wi];
					HelperFunctions::toLower(lowerWord);

					// add the word ( de-dup happens here )
					int wordIndex = _ws.addWord(lowerWord);
					eWs.emplace_back(wordIndex, fieldIndex, wi);
				}
			}

			// key will never be found if no strings, so don't add
			if (eWs.size() < 1)
				return;

			// sort indices ( in memory-order )
			std::sort(eWs.begin(), eWs.end());

			// keep the lowest index-in-field
			for (size_t i = 1; i < eWs.size(); ++i)
			{
				if (eWs[i - 1]._wordIndex != eWs[i]._wordIndex)
					continue;

				if (eWs[i - 1]._fieldIndex != eWs[i]._fieldIndex)
					continue;

				// store lower
				int v0 = eWs[i - 1]._wordIndexInField;
				int v1 = eWs[i]._wordIndexInField;
				if (v1 < v0)
				{
					v0 = v1;
				}
				eWs[i - 1]._wordIndexInField = v0;
				eWs[i]._wordIndexInField = v0;
			}

			eWs.erase(std::unique(eWs.begin(), eWs.end()), eWs.end());

			// finally add
			_entries.push_back(e);
		}

		// each field can have a weight (defaults to 1)
		void setWeights(const std::vector<float>& fieldWeights)
		{
			// ensure we have enough weights
			while (_fieldWeights.size() < fieldWeights.size())
				_fieldWeights.push_back(1.0f);

			for (size_t i = 0; i < _fieldWeights.size(); ++i)
				_fieldWeights[i] = fieldWeights[i];
		}

		// only used for debugging
		int debugGetWordCount()
		{
			return (int)_ws._wordEnd.size();
		}

		// any search-result scoring below this will not be returned from the search
		void setThreshold(float threshold)
		{
			_threshold = threshold;
		}

		// returns a big list of results ( sorted and with a score )
		std::vector< Result > search(std::string queryString) const
		{
			std::vector< Result > resultsWithKey;

			// mirrors all entries
			_tempResults.resize(_entries.size());
			_tempResultsOrderPenalty.resize(_entries.size());

			// 0. prepare query (query-string -> query-words)
			auto queryWords = HelperFunctions::splitString(queryString);
			for (size_t i = 0; i < queryWords.size(); ++i)
				HelperFunctions::toLower(queryWords[i]);

			// 1. loop over each word in query
			size_t qwss = queryWords.size();
			for (size_t qi = 0; qi < qwss; ++qi)
			{
				const std::string& queryWord = queryWords[qi];

				// 2. score every word against this query-word
				scoreEveryWord(_scorePerWord, _ws, queryWord);

				// 3. score each entry
				scoreEveryEntry(qi);
			}

			if (qwss > 1)
			{
				// we need to apply the order-penalty
				for (size_t i = 0; i < _tempResultsOrderPenalty.size(); ++i)
				{
					TempResultOrderPenalty& penalty = _tempResultsOrderPenalty[i];
					const int misses = penalty._misses;
					if (misses > 0)
					{
						float p = 1.0f / (1.0f + misses * 0.1f);
						_tempResults[i]._score *= p;
					}
				}
			}


			// at this point all scores are in tempResults vector
			// only sorting left

			// create a lower threshold for multi-word-queries
			float threshold = _threshold;
			for (size_t i = 1; i < qwss; ++i)
			{
				threshold *= _threshold;
			}

			// erase below threshold
			_tempResults.erase(std::remove_if(_tempResults.begin(), _tempResults.end(), [&](TempResult tr) { return tr._score < threshold; }), _tempResults.end());

			// sort all that remain
			std::sort(_tempResults.begin(), _tempResults.end());

			// finally copy to the result vector
			resultsWithKey.resize(_tempResults.size());
			for (size_t i = 0; i < _tempResults.size(); ++i)
			{
				const TempResult& src = _tempResults[i];
				Result& dst = resultsWithKey[i];
				dst.score = src._score;
				dst.key = _entries[(size_t)src._entryIndex]._key;
			}

			return resultsWithKey;
		}

	};

}

#ifdef _MSC_VER
#pragma warning(pop) 
#endif

#endif // FUZZY_SEARCH_DATABASE_HPP
