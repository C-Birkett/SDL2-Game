#pragma once

typedef struct Animation
{
  int m_index;
  int m_frames;
  int m_speed;

  Animation() {}
  Animation(int i, int f, int s)
  : m_index(i), m_frames(f), m_speed(s)
  {
  }
}Animation;
