#ifndef GRAPH_H
#define GRAPH_H
#include "../gameobject.hpp"
#include "../shader.hpp"

class Graph : public GameObject {
 public:
  Graph() {
    graph = GPU_CreateImage(270, 80, GPU_FORMAT_RGBA);
    //    GPU_SetImageFilter(graph, GPU_FILTER_NEAREST);
    GPU_SetWrapMode(graph, GPU_WRAP_NONE, GPU_WRAP_NONE);

    graphtarget = GPU_LoadTarget(graph);

    // Load shader
    graphshader = new Shader(
        "Graph", {"DeltaTime", "UpdateTime", "DrawTime", "GraphMax"});
    uniforms = graphshader->GetUniforms();
  }

  ~Graph() {
    GPU_FreeTarget(graphtarget);
    GPU_FreeImage(graph);
    delete graphshader;
  }

  void Draw() {
    GPU_SetBlendMode(graph, GPU_BLEND_NORMAL);
    graphshader->Activate();
    GPU_SetUniformf(uniforms["DeltaTime"], globals->DeltaTime);
    GPU_SetUniformf(uniforms["UpdateTime"], globals->updateTime);
    GPU_SetUniformf(uniforms["DrawTime"], globals->drawTime);
    GPU_SetUniformf(uniforms["GraphMax"], 20.0);
    GPU_Blit(graph, nullptr, graphtarget, 270 / 2, 40);
    graphshader->Deactivate();
    //    GPU_SetBlendMode(graph, GPU_BLEND_SET);
    GPU_SetBlendFunction(graph, GPU_FUNC_ONE, GPU_FUNC_ONE_MINUS_SRC,
                         GPU_FUNC_SRC_ALPHA, GPU_FUNC_DST_ALPHA);
    GPU_Blit(graph, nullptr, globals->backbuffer, 270 / 2, position.y);
  }

 private:
  GPU_Image*  graph;
  GPU_Target* graphtarget;
  Shader*     graphshader;

  map<string, uint> uniforms;
};

#endif
