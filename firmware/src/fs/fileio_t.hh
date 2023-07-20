#include <functional>
#include <span>
#include <string_view>

using FileAction = std::function<void(const std::string_view filename, uint32_t timestamp, uint32_t filesize)>;

template<typename T>
concept FileIoC = requires(T t,
						   const std::string_view filename,
						   const std::span<const char> const_data,
						   std::span<char> read_buffer,
						   FileAction action,
						   uint32_t tm) {
					  {
						  t.update_or_create_file(filename, const_data)
						  } -> std::convertible_to<bool>;
					  {
						  t.foreach_file_with_ext(filename, action)
						  } -> std::convertible_to<bool>;
					  {
						  t.read_file(filename, read_buffer)
						  } -> std::integral;
					  {
						  t.volname()
						  } -> std::convertible_to<std::string_view>;
					  {
						  t.is_mounted()
						  } -> std::same_as<bool>;

					  t.delete_file(filename);
					  t.set_file_timestamp(filename, tm);
				  };
