#include "x.h"


int main(int argc, char** argv)
{
  x_stopwatch_cu ttl;
  x_stopwatch_cu avg;
  x_stopwatch_stats stats;

  ttl.tic();
  x_log('i', nullptr, "[ttl] Stopwatch starts.");

  for (size_t i = 0; i < 5; ++i) {
    avg.tic();
    x_sleep(1000);
    avg.toc(stats, "ms", 3);
  }
  if (stats.ready) {
    stats.echo();
  }

  stats.reset();

  for (size_t i = 0; i < 5; ++i) {
    avg.tic();
    x_sleep(1000);
    avg.toc(stats, "ms", 5);
  }
  if (stats.ready) {
    stats.echo();
  }

  ttl.toc("ms");
  x_log('i', nullptr, "[ttl] Stopwatch stops.", ttl.elapsed());
  x_log('p', nullptr, "[ttl] Total: %fms", ttl.elapsed());

  return 0;
}
