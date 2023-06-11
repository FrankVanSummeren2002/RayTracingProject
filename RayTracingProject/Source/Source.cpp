#include "precomp.h"
#include "Ray.h"
#include "Rendering/Screen.h"
#include "Shapes/Shapes.h"
#include "Shapes/box.h"
#include "Shapes/plane.h"
#include "Shapes/sphere.h"
#include "ObjectManager.h"
#include "thread"
/// 
/// read the ReadMe first
///

ObjectManager objectmanager;
Screen screen;
const int Threads = 16;
vec3 Acumilator[static_cast<unsigned int>(SCRWIDTH * SCRHEIGHT)];
float division;
const int scene = 8;
void threadingTask(int MinX, int MaxX, int MinY, int MaxY,int& seed);
int main()
{
    std::thread threads[Threads];
    sf::Clock clock;
    float DeltaTime = 0;
    int SpeedIncrease = 1;
    int FrameNumb = 0;
    for (int y = 0; y < SCRHEIGHT; y++)
    {
        for (int x = 0; x < SCRWIDTH; x++)
        {
            Acumilator[x * static_cast<int> (SCRHEIGHT) + y] = vec3(0, 0, 0);
        }
    }
    sf::Time Time = clock.getElapsedTime();
    int seed = static_cast<int>(Time.asMicroseconds());

    vec3 N = vec3(0, -1, 0);
    vec3 P = vec3(0, 4, -50);
 
    switch (scene)
    {
    case 3:
    {
        objectmanager.AddPointLight(new LightSource(vec3(7, -10, -10), vec3(2, 2, 2), 10));
        objectmanager.AddShape(new plane(N, P, BLACK, Material::material::diffuse, true, WHITE, vec3(0, 0, 0), Material::material::TheVoid, 1, 0, 0, 0), false);
        objectmanager.AddShape(new Sphere(4, vec3(0, 0, -20), RED, Material::material::reflective), true);
        objectmanager.SetVoidColor(BLACK);
        
        break;
    }
    case 4:
    {
        objectmanager.AddPointLight(new LightSource(vec3(5, -10, -5), vec3(2, 2, 2), 10));
        objectmanager.AddShape(new plane(N, P, BLACK, Material::material::diffuse, true, WHITE, vec3(0, 0, 0), Material::material::TheVoid, 1, 0, 0, 0), false);
        objectmanager.AddShape(new Sphere(4, vec3(0, 0, -15), (WHITE + BLACK) * 0.5, Material::material::reflective,vec3(0,0,0),Material::material::diffuse,0.5), true);
        objectmanager.SetVoidColor(BLACK);
        break;
    }
    case 5:
    {
        objectmanager.AddShape(new plane(N, P, RED,  Material::material::diffuse, true, (RED + GREEN)*0.5 , vec3(0, 0, 0), Material::material::TheVoid, 1, 20, 0, 50), false);
        objectmanager.AddShape(new Sphere(4, vec3(-2, -5, -20), WHITE, Material::material::glass), true);
        objectmanager.AddShape(new Sphere(3.7f, vec3(-2, -5, -20), WHITE, Material::material::glass), true);
        objectmanager.AddShape(new Sphere(4, vec3(5, -2, -30), BLUE, Material::material::reflective,vec3(0,0,0),Material::material::diffuse,0.8f), true);
        objectmanager.AddPointLight(new LightSource(vec3(0, -100, 0), vec3(2, 2, 2), 200));
        objectmanager.SetVoidColor((BLUE + WHITE + WHITE) * 0.3333);
        screen.setEye(vec3(0,-5,0));
        break;
    }
    case 6:
    {
         N = vec3(0, 0, 1);
         P = vec3(0, 0, -20);
        objectmanager.AddShape(new plane(N, P, WHITE, Material::material::diffuse, false,WHITE, vec3(0, 0, 0), Material::material::TheVoid, 1, 20, 20, 0), true);
        N = vec3(1, 0, 0);
        P = vec3(20, 0, 0);
        objectmanager.AddShape(new plane(N, P, GREEN,  Material::material::diffuse, false,GREEN, vec3(0, 0, 0), Material::material::TheVoid, 1, 0, 20, 20),true);
        N = vec3(1, 0, 0);
        P = vec3(-20, 0, 0);
        objectmanager.AddShape(new plane(N, P, RED,  Material::material::diffuse, false, RED,vec3(0, 0, 0), Material::material::TheVoid, 1, 0, 20, 20), true);
        N = vec3(0, 1, 0);
        P = vec3(0, -20, 0);
        objectmanager.AddShape(new plane(N, P, WHITE,  Material::material::diffuse, false, WHITE, vec3(0, 0, 0), Material::material::TheVoid, 1, 20, 0, 20), true);
        N = vec3(0, 1, 0);
        P = vec3(0, 20, 0);
        objectmanager.AddShape(new plane(N, P, WHITE,  Material::material::diffuse, false,WHITE, vec3(0, 0, 0), Material::material::TheVoid, 1, 20, 0, 20), true);
        N = vec3(0, 0, 1);
        P = vec3(0, 0, 40);
        objectmanager.AddShape(new plane(N, P, BLUE * 0.75, Material::material::diffuse, false, BLUE, vec3(0, 0, 0), Material::material::TheVoid, 1, 0, 0, 0), true);

        objectmanager.AddShape(new Sphere(4, vec3(-5, 12, 5), WHITE * 0.75, Material::material::reflective, vec3(0.5f, 0.5f, 0.5f), Material::material::GlossyReflection, 1), true);
        objectmanager.AddShape(new Sphere(4, vec3(10, 16, 4), WHITE * 0.75, Material::material::reflective, vec3(0.7f, 0.7f, 0.5f), Material::material::GlossyReflection, 1), true);
        screen.setEye(vec3(0, 2, 40));

        objectmanager.AddShape(new Box(4, 10, 4, vec3(-10, 10, -10), WHITE, Material::material::reflective, vec3(0.5, 0.5, 0.5), 0, -65, 0), true);

        objectmanager.AddAreaLight(new AreaLight(new Sphere(5, vec3(0, -12, -4), vec3(2, 2, 2), Material::material::diffuse), 10), true);
        break;
    }
    case 7:
    {
        objectmanager.SetVoidColor((BLUE + WHITE + WHITE) * 0.3333);
        objectmanager.AddPointLight(new LightSource(vec3(0, -100, 0), vec3(2, 2, 2), 200));
        objectmanager.AddShape(new plane(N, P, (BLACK+WHITE)*0.5, Material::material::diffuse, false, WHITE, vec3(0, 0, 0), Material::material::TheVoid, 1, 0, 0), false);
        for (int i = 0; i < 99; i++)
        {
          objectmanager.AddShape(new Box(2, 5, 3, vec3(static_cast<float>(math::RANDI_MIN_MAX(seed, 100, -100)), static_cast<float>(math::RANDI_MIN_MAX(seed, 5, -20)), static_cast<float>(math::RANDI_MIN_MAX(seed, 100, -100))), vec3(math::RANDF_MIN_MAX(seed, 1.f, 0.f), math::RANDF_MIN_MAX(seed, 1.f, 0.f), math::RANDF_MIN_MAX(seed, 1.f, 0.f)), Material::material::diffuse, vec3(1, 1, 1), math::RANDI_MIN_MAX(seed, 360, 0), math::RANDI_MIN_MAX(seed, 360, 0), math::RANDI_MIN_MAX(seed, 360, 0)), true);
        }
         break;
    }
    case 8:
	    {
        objectmanager.SetVoidColor(WHITE);
        objectmanager.AddShape(new Sphere(1, vec3(0, 0, -4), vec3(1, 1, 1), Material::material::diffuse), false);
        N = vec3(0, 0, 1);
        P = vec3(0, 0, -5);
        objectmanager.AddShape(new plane(N, P, WHITE, Material::material::diffuse, false, WHITE, vec3(0, 0, 0), Material::material::TheVoid, 1, 20, 20, 0), true);
        objectmanager.AddPointLight(new LightSource(vec3(2, -2, 0), vec3(1, 0, 0), 4));
        objectmanager.AddPointLight(new LightSource(vec3(-2, -2, 0), vec3(0, 1, 0), 4));
        objectmanager.AddPointLight(new LightSource(vec3(0, 2, 0), vec3(0, 0, 1), 4));
        break;
	    }
    default:
      objectmanager.SetVoidColor((BLUE + WHITE + WHITE) * 0.3333);
      N = vec3(0,1,0);
      P = vec3(0,5,0);
      objectmanager.AddPointLight(new LightSource(vec3(0, -100, 0), vec3(2, 2, 2), 200));
      objectmanager.AddShape(new plane(N, P, WHITE, Material::material::diffuse,true,BLACK), false);
      

      objectmanager.AddShape(new Sphere(3, vec3(10, 0, -10), RED, Material::material::glass, vec3(0, 0, 0)), true);
      objectmanager.AddShape(new Sphere(2.9f, vec3(10, 0, -10), RED, Material::material::glass, vec3(0, 1, 1)), true);
      objectmanager.AddShape(new Sphere(0.5f, vec3(10, 0, -10), BLUE, Material::material::diffuse, vec3(0, 0,0)), true);
      objectmanager.AddShape(new Sphere(3, vec3(10, 0, 10), BLUE, Material::material::reflective, vec3(0, 0, 0)), true);
     
      objectmanager.AddShape(new Box(1, 1, 1, vec3(0, 0, -10), RED, Material::material::glass, vec3(0, 1, 1), 0, 40, 0), true);
      objectmanager.AddShape(new Box(1, 5, 1, vec3(-10, 0, 10), RED, Material::material::diffuse, vec3(0, 0, 0), 20, 40, 20), true);
      

      for (int i = 0; i < 25; i++)
      {
          objectmanager.AddShape(new Sphere(3, vec3(static_cast<float> (math::RANDI_MIN_MAX(seed, 100, -100)), static_cast<float>(math::RANDI_MIN_MAX(seed, 5, -20)), static_cast<float>(math::RANDI_MIN_MAX(seed, -20, -100))), vec3(math::RANDF_MIN_MAX(seed, 1.f, 0.f), math::RANDF_MIN_MAX(seed, 1.f, 0.f), math::RANDF_MIN_MAX(seed, 1.f, 0.f)), Material::material::diffuse), true);
          objectmanager.AddShape(new Box(2, 5, 3, vec3(static_cast<float>(math::RANDI_MIN_MAX(seed, 100, -100)), static_cast<float>(math::RANDI_MIN_MAX(seed, 5, -20)), static_cast<float>(math::RANDI_MIN_MAX(seed, 20, 100))), vec3(math::RANDF_MIN_MAX(seed, 1.f, 0.f), math::RANDF_MIN_MAX(seed, 1.f, 0.f), math::RANDF_MIN_MAX(seed, 1.f, 0.f)), Material::material::diffuse, vec3(1, 1, 1), math::RANDI_MIN_MAX(seed, 360, 0), math::RANDI_MIN_MAX(seed, 360, 0), math::RANDI_MIN_MAX(seed, 360, 0)), true);
      }
      break;
    }

     objectmanager.createBVH();
  
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(SCRWIDTH), static_cast<unsigned int>(SCRHEIGHT)), "RayTracer");
    
    window.clear();
    while (window.isOpen())
    {
        screen.getEye();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        clock.restart();
        FrameNumb++;
        
       

        //rotation
        //if the delta time becomes to low we cant move so i chose to set a limit on the lowest posible delta time
        bool movement = false;

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) == true)
            SpeedIncrease = 2;

        else
            SpeedIncrease = 1;

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) == true)
        {
            screen.rotateScreen(0, static_cast<float>(-20.f * DeltaTime * SpeedIncrease), 0);
            movement = true;
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) == true)
        {
            screen.rotateScreen(0,static_cast<float> (20.f * DeltaTime * SpeedIncrease), 0);
            movement = true;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) == true)
        {
            screen.rotateScreen(static_cast<float>(-20.f * DeltaTime * SpeedIncrease), 0, 0);
            movement = true;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) == true)
        {
            screen.rotateScreen(static_cast<float>(20.f * DeltaTime * SpeedIncrease), 0, 0);
            movement = true;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) == true)
        {
            screen.rotateScreen(0, 0, static_cast<float>(20.f * DeltaTime * SpeedIncrease));
            movement = true;

        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E)) == true)
        {
            screen.rotateScreen(0, 0,static_cast<float> (-20.f * DeltaTime * SpeedIncrease));
            movement = true;
        }
        //movemement
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)) == true)
        {
            screen.setEye(screen.getEye() - screen.getScreenDir()* (10.f * DeltaTime * SpeedIncrease ));
            movement = true;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) == true)
        {
            screen.setEye(screen.getEye() + screen.getScreenDir()*(10.f * DeltaTime * SpeedIncrease));
            movement = true;
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) == true)
        {
            movement = true;
            screen.setEye(screen.getEye() - screen.getXaxis()*(10.f * DeltaTime * SpeedIncrease));
        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) == true)
        {
            movement = true;
            screen.setEye(screen.getEye() + screen.getXaxis()*( 10.f* DeltaTime * SpeedIncrease));
        }
        if (movement == true)
        {
            for (int y = 0; y < SCRHEIGHT; y++)
                for (int x = 0; x < SCRWIDTH; x++)
               Acumilator[x * static_cast<int> (SCRHEIGHT) + y] = vec3(0,0,0);  
            FrameNumb = 1;
            movement = false;
        }
        division = 1.f / static_cast<float>(FrameNumb);
        

        int width = static_cast<int>(SCRWIDTH) / Threads;
        for (int i = 0; i < Threads; i++)
        {
            threads[i] = std::thread(threadingTask, 0, 512, i * width, i * width + width,std::ref(seed));
        }
        for (int i = 0; i < Threads; i++)
        {
            threads[i].join();
        }
        
        screen.SetScreen();
        window.draw(screen.getImage());
        window.display();
        
        Time = clock.getElapsedTime();
        DeltaTime = static_cast<float>(Time.asSeconds());
        printf("%f\n", DeltaTime);
    }
   
    return 0;
}

void threadingTask(int MinX, int MaxX,int MinY,int MaxY,int& seed)
{
    vec3 color;
    vec3 eye;
    vec3 ScreenPos;
    eye = screen.getEye();
    Ray* raytrace;
    raytrace = new Ray(eye);
    raytrace->ClearIndex();
    for (int y = MinY; y < MaxY; y++)
    {
        for (int x = MinX; x < MaxX; x++)
        {
            raytrace->setOr(eye);
            raytrace->ClearIndex();
            ScreenPos = screen.CurrcentScreenPos(x, y,seed);

            raytrace->Init(ScreenPos);
            color = objectmanager.RayColor(raytrace, RECURSIONCAP,seed);
            color = math::Vecclamp(color, 0, 1);
            Acumilator[x + static_cast<int>(SCRHEIGHT) * y] += color;
            color = Acumilator[x + static_cast<int>(SCRHEIGHT) * y] * division;

            screen.draw(x, y, color.x, color.y, color.z);
        }
    }
    delete raytrace;
}