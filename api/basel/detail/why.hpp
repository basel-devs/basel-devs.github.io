#ifndef BASEL_BASEL_WHY_HPP
#define BASEL_BASEL_WHY_HPP

//#define cimg_display 0
//#include <CImg.h>
//
//#include <emscripten/val.h>
//#include <js/bind.hpp>

auto basel::devs_t::why() const {
/*
  using namespace cimg_library;

  const unsigned char
    white[]  = { 255, 255, 255 }, black[] = { 0, 0, 0 }, red[] = { 120, 50, 80 },
    yellow[] = { 200, 155, 0 }, green[] = { 30, 200, 70 }, purple[] = { 175, 32, 186 },
    blue[] = { 55, 140, 185 }, grey[] = { 127, 127, 127 };

  float
    rx = 0, ry = 0, t = 0, gamma = 0, vgamma = 0, T = 0.9f,
    nrx = (float)(2*cimg::rand(-1,1)),
    nry = (float)(2*cimg::rand(-1,1));
  int y0 = 2*13;

  CImg<unsigned char> back(1,2,1,3,10), img;
  back.fillC(0,1,0,10,10,235).resize(800,600,1,3,3).get_shared_channel(2).noise(10,1).draw_plasma();
  back.draw_rectangle(0,y0 - 7,back.width() - 1,y0 + 20,red);

//  CImgDisplay disp(back,"My Bubble",0,false,true);
//  disp.move((disp.screen_width() - disp.window_width())/2,(disp.screen_height() - disp.window_height())/2);
  img = back; back*=0.15f;

  //for (;;) {
  auto draw = []() {
    img*=0.85f; img+=back;
    for (int i = 0; i<60; ++i) {
      const float
        mx = (float)(img.width()/2 + (img.width()/2 - 30)*((1 - gamma)*std::cos(3*t + rx*i*18.0f*cimg::PI/180) +
                                                     gamma*std::cos(3*t + nrx*i*18.0f*cimg::PI/180))),
        my = (float)(img.height()/2 + (img.height()/2 - 30)*((1 - gamma)*std::sin(4*t + ry*i*18.0f*cimg::PI/180) +
                                                     gamma*std::sin(4*t + nry*i*18.0f*cimg::PI/180))),
        mz = (float)(1.3f + 1.2f*((1 - gamma)*std::sin(2*t + (rx + ry)*i*20*cimg::PI/180) +
                                  gamma*std::sin(2*t + (nrx + nry)*i*20*cimg::PI/180)));
      const int j = i%5;
      img.draw_circle((int)mx,(int)my,(int)(10*mz),j!=0?(j!=1?(j!=2?(j!=3?green:red):yellow):purple):blue,0.2f).
        draw_circle((int)(mx + 4*mz),(int)(my - 4),(int)(3*mz),white,0.1f).
        draw_circle((int)mx,(int)my,(int)(10*mz),black,0.2f,~0U);
    }
    //disp.resize(disp,false).display(img).wait(25);
    gamma+=vgamma;
    if (gamma>1) {
      gamma = vgamma = 0;
      rx = nrx;
      ry = nry;
      nrx=(float)(2*cimg::rand(-1,1)); nry=(float)(2*cimg::rand(-1,1));
    }
    t+=0.006f; T+=0.005f; if (T>1) { T-=(float)(1 + cimg::rand(-1,1)); vgamma = 0.03f; }
 
  }

  using emscripten::val;
  val imgData=ctx.getImageData(0,0,800,600);
  ctx.putImageData(imgData,10,70);

  return R"(<canvas id="why_canvas" width="800" height="600" style="border:1px solid #FFFFFF;" ></canvas> )" */

  return R"(
    <h1 style="vertical-align:middle; text-align:center;">Because API is art...</h1>
    <h1 style="vertical-align:middle; text-align:center;">Because we live for coding...</h1>
    <h1 style="vertical-align:middle; text-align:center;">Because we believe we can unite to innovate...</h1>
    <h1 style="vertical-align:middle; text-align:center;">Because what does not exists, the programmer will do it.</h1>
  )";
}

#endif
