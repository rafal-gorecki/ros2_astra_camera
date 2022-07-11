#include "astra_camera/ob_timer_filter.h"

namespace astra_camera {
OBTimerFilter::OBTimerFilter(std::size_t buffer_len)
    : buffer_len_(buffer_len), logger_(rclcpp::get_logger("OBTimerFilter")) {}

OBTimerFilter::~OBTimerFilter() = default;

void OBTimerFilter::addSample(double sample) {
  buffer_.push_back(sample);
  if (buffer_.size() > buffer_len_) buffer_.pop_front();
}

double OBTimerFilter::getMedian() {
  if (!buffer_.empty()) {
    std::deque<double> sort_buffer = buffer_;

    std::sort(sort_buffer.begin(), sort_buffer.end());

    return sort_buffer[sort_buffer.size() / 2];
  } else {
    return 0.0;
  }
}

double OBTimerFilter::getMovingAvg() {
  if (!buffer_.empty()) {
    double sum = 0;

    auto it = buffer_.begin();
    auto it_end = buffer_.end();

    while (it != it_end) {
      sum += *(it++);
    }

    return sum / static_cast<double>(buffer_.size());
  } else
    return 0.0;
}

void OBTimerFilter::clear() { buffer_.clear(); }
}  // namespace astra_camera
