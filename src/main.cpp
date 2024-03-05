#include "Camera.hpp"
#include "Scene.hpp"
#include "Shapeset.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"
#include "OBJ_Loader.h"
#include <memory>

int main(int, char **)
{
	raytracer::Vector origin{0, 0, 0}, xVec{1, 0, 0}, yVec{0, 1, 0}, zVec{0, 0, 1};
	raytracer::Vector4 xVec4{xVec}, yVec4{yVec}, zVec4{zVec}, tVec{0.0, 0.0, 0.0, 1.0};

	auto tMat = raytracer::translationMatrix(3, 0, 5);
	auto rXMat = raytracer::rotXMatrix(90);
	auto rYMat = raytracer::rotYMatrix(90);
	xVec4 = rYMat.apply(xVec4);
	std::cout << xVec4 << "\n\n";
	

	//raytracer::Camera camera{ 2* zVec, -zVec, yVec, 45, 1};
	//raytracer::Camera camera{ 10* zVec + 3*yVec + xVec, -zVec, yVec, 45, 1};

	raytracer::Camera camera{1.5*zVec + 1.5*yVec + 1.5*xVec, origin, yVec, 45, 1};
	//raytracer::Camera camera{0.2*zVec, zVec, yVec, 45, 1};
	//raytracer::Camera camera{10*zVec, origin, yVec, 45, 1};
	raytracer::Plane xzPlane{origin, yVec};
	raytracer::Plane yzPlane{-xVec, xVec};
	// auto shapes = raytracer::ShapeSet{{&sphere, &triangle, &triangle2, &xzPlane}};
	//auto shapes = raytracer::ShapeSet{{new raytracer::Plane{{0, -1, 0}, {0, 1, 0}}}};
	auto shapes = raytracer::ShapeSet{{}};
	// auto shapes = ShapeSet{{&triangle, &triangle2, &sphere}};
	auto light = raytracer::Light{{5, 5, 5}};
	auto light1 = raytracer::Light{{0, 0, 0}};
	auto light2 = raytracer::Light{{1, 0, 0}};
	auto lights = {light};
	auto loaderPointer = std::make_unique<objl::Loader>(objl::Loader{});
	//loaderPointer->LoadFile("/home/christian/Desktop/RayTracer-temp/models/cube.obj");
	//loaderPointer->LoadFile("/home/christian/Desktop/RayTracer-temp/models/dice.obj");
	auto scene = raytracer::Scene{lights, shapes, camera};
	scene.addShapes(std::move(loaderPointer));
	auto tri0 = new raytracer::Triangle{{1, 1, 1}, {1, 0, 1}, {0, 1, 1}};
	auto tri1 = new raytracer::Triangle{{0, 1, 1}, {0, 0, 1}, {1, 0, 1}};
	auto tri2 = new  raytracer::Triangle{{0, 1, 0}, {0, 0, 0}, {0, 1, 1}};
	auto tri3 = new  raytracer::Triangle{{0, 0, 1}, {0, 0, 0}, {1, 0, 0}};
	auto tri4 = new  raytracer::Triangle{{1, 0, 1}, {1, 0, 0}, {1, 1, 0}};
	auto tri5 = new  raytracer::Triangle{{1, 0, 0}, {0, 0, 0}, {0, 1, 0}};
	auto tri6 = new  raytracer::Triangle{{0, 1, 1}, {1, 1, 1}, {0, 1, 0}};
	auto tri7 = new  raytracer::Triangle{{0, 1, 1}, {0, 0, 1}, {1, 1, 1}};
	auto tri8 = new  raytracer::Triangle{{0, 1, 0}, {0, 0, 0}, {0, 1, 1}};
	auto tri9 = new  raytracer::Triangle{{1, 0, 1}, {0, 0, 1}, {1, 0, 0}};
	auto tri10 = new raytracer::Triangle{{1, 1, 1}, {1, 0, 1}, {1, 1, 0}};

	auto tri11 = new raytracer::Triangle{{1, 1, 0}, {1, 0, 0}, {0, 1, 0}};
	auto tri12 = new raytracer::Triangle{{1, 1, 0}, {0, 1, 0}, {1, 1, 1}};
	scene.addShape(tri0);
	scene.addShape(tri1);
	scene.addShape(tri2);
	scene.addShape(tri3);
	scene.addShape(tri4);
	scene.addShape(tri5);
	scene.addShape(tri6);
	scene.addShape(tri7);
	scene.addShape(tri8);
	scene.addShape(tri9);
	scene.addShape(tri10);
	scene.addShape(tri11);
	scene.addShape(tri12);
	scene.render(1000, 1000);
}
