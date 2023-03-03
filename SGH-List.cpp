#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

#include <iostream>
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    /*  set up  Dear ImGui  */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //style

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    /*==============================================================================================
    *   VELUS
   =================================================================================================*/
   //window open velus
    bool statestik = false, ImGuiDemo = false,
        make_list_file = false, print_2_file = false;
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    //Valu for Upgrade array's                                                           //ARRAY FOR VER VERDI PER UPGRADE, STYRES AV I FRA FORLOOP
    std::string uppgradeNameArray[200][20];
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 20; j++) {
            uppgradeNameArray[i][j] = "";
        }
    };

    int uppgradeCostArray[200][20];                                         //UNTAK UPPGARDE NR SOM HOLDER ANATALE UPGRADES 
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 20; j++) {
            uppgradeCostArray[i][j] = 0;
        }
    };

    static char listName[32] = "";

    int uppgradeCost = 0, uppgradeNr = 0, uppgradeNrArray[20] = {},
        unitFigerCount[200] = {}, UnitNr = 3, unitCost[200] = {};

    int floot_int = 0;                                   // for side menyen i add unit

    // sett upgrade velus
    int         uppgradeSelected = 0;
    int         unitSelected = 0;
    int         setUppgradeCost = 0;
    static char setUppgradeName[32] = "";
    bool        showNote[20] = { false };

    //per unit verdier
    static char unitName[200][32] = { {} };

    static char unitNotw[200][255 * 6] = { {} };



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Nye Frame */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //**

        if (ImGuiDemo)
        {
            ImGui::ShowDemoWindow();
        }

        if (statestik)
        {
            ImGui::Begin("statestik", &statestik);
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                ImGui::BeginChild("uppgarde Name Array", ImVec2(ImGui::GetContentRegionAvail().x * 0.20f, 260), false, window_flags);
                ImGui::Text("uppgarde Name Array");

                for (int i = 0; i < 200; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        ImGui::Text("|%d|%d|> %s", i, j, uppgradeNameArray[i][j].c_str());
                    }
                }

                ImGui::EndChild();
            }
            ImGui::SameLine();
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                ImGui::BeginChild("uppgarde cost Array", ImVec2(ImGui::GetContentRegionAvail().x * 0.24f, 260), false, window_flags);
                ImGui::Text("uppgrade cost array");                                   //UNTAK UPPGARDE NR SOM HOLDER ANATALE UPGRADES 

                for (int i = 0; i < 200; i++)
                {
                    for (int j = 0; j < 20; j++)
                    {
                        ImGui::Text("|%d|%d|> %d", i, j, uppgradeCostArray[i][j]);
                    }
                }
                ImGui::EndChild();
            }
            ImGui::SameLine();
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                ImGui::BeginChild("uppgarde Nr Array", ImVec2(ImGui::GetContentRegionAvail().x * 0.31f, 260), false, window_flags);
                ImGui::Text("uppgarde Nr Array");

                for (int i = 0; i < 20; i++)
                {
                    ImGui::Text("|%d| %d ", i, uppgradeNrArray[i]);
                }
                ImGui::EndChild();
            }

            ImGui::SameLine();
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                ImGui::BeginChild("unit name array", ImVec2(ImGui::GetContentRegionAvail().x * 0.38f, 260), false, window_flags);
                ImGui::Text("unit name array");                                   //UNTAK UPPGARDE NR SOM HOLDER ANATALE UPGRADES 

                for (int i = 0; i < 200; i++)
                {
                    ImGui::Text("|%d|> %s", i, unitName[i]);
                };

                ImGui::EndChild();
            }
            ImGui::SameLine();
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                ImGui::BeginChild("unit figur count array", ImVec2(ImGui::GetContentRegionAvail().x * 0.50f, 260), false, window_flags);
                ImGui::Text("figur count");                                   //UNTAK UPPGARDE NR SOM HOLDER ANATALE UPGRADES 

                for (int i = 0; i < 200; i++)
                {
                    ImGui::Text("|%d|> %d", i, unitFigerCount[i]);
                };

                ImGui::EndChild();
            }
            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                ImGui::BeginChild("Rendom velus", ImVec2(ImGui::GetContentRegionAvail().x * 0.99f, 260), false, window_flags);

                ImGui::Text(" <floot_int> "); ImGui::SameLine();
                ImGui::Text("%d", floot_int); ImGui::SameLine();
                ImGui::Text(" <uppgradeNr> "); ImGui::SameLine();
                ImGui::Text("%d", uppgradeNr); ImGui::SameLine();
                ImGui::Text(" <uppgradeCost> "); ImGui::SameLine();
                ImGui::Text("%d", uppgradeCost); ImGui::SameLine();
                ImGui::Text(" <List Name> "); ImGui::SameLine();
                ImGui::Text("%s", listName); ImGui::SameLine();

                ImGui::EndChild();
            }
            ImGui::End();
        }

        if (make_list_file)
        {
           // PrintFILE x;
            //x.createFile(listName);
            make_list_file = false;
        }

        if (print_2_file)
        {
            //PrintFILE x;
            //x.writeList(listName, uppgradeNameArray, uppgradeCostArray,
               // uppgradeNrArray, unitFigerCount, unitCost, unitName, unitNotw, UnitNr);
            print_2_file = false;
        }

        ImVec2 winSiz;
        ImVec2 posMainWin;
        posMainWin.x = 0;
        posMainWin.y = 0;
        winSiz.x = io.DisplaySize.x;
        winSiz.y = io.DisplaySize.y;
        ImGui::SetNextWindowSize(winSiz);
        ImGui::SetNextWindowPos(posMainWin);
        {                                                                       // start på hoved vindu i ImGui
            ImGuiWindowFlags main_window_flags = 0;
            main_window_flags |= ImGuiWindowFlags_NoTitleBar;
            main_window_flags |= ImGuiWindowFlags_MenuBar;
            main_window_flags |= ImGuiWindowFlags_NoResize;
            main_window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            ImGui::Begin("Main", NULL, main_window_flags);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Menu"))                                   //Top bar meny
                {
                    ImGui::MenuItem("debug", NULL, &statestik);                 // short cut for statestik
                    ImGui::MenuItem("demo windo", NULL, &ImGuiDemo);            //vis imguidemo vindu
                    ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Print"))                                  // queek print menu
                {
                    ImGui::MenuItem("Make .txt list", NULL, &make_list_file);   // make a .txt file
                    ImGui::MenuItem("Update List", NULL, &print_2_file);        // Uppdate List

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;


            {
                ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                ImGui::BeginChild("List side", ImVec2(ImGui::GetContentRegionAvail().x * 0.7f, winSiz.y), false, window_flags);
                {
                    ImGui::BeginChild("topPartL", ImVec2(ImGui::GetContentRegionAvail().x * 0.7f, 30), false, ImGuiWindowFlags_NoScrollbar);

                    ImGui::Text("List name:");
                    ImGui::SameLine();
                    ImGui::InputText("##", listName, IM_ARRAYSIZE(listName));

                    ImGui::EndChild();
                }
                ImGui::SameLine();
                {
                    ImGui::BeginChild("topPartR", ImVec2(ImGui::GetContentRegionAvail().x * 1.0f, 30), false, ImGuiWindowFlags_NoScrollbar);

                    ImGui::Text("Nr Of Unit's ->");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(90);
                    ImGui::InputInt("##", &UnitNr);

                    ImGui::EndChild();
                }

                for (int row = 0; row < UnitNr; row++)
                {
                    if (ImGui::BeginTable("Man Rap", 1, ImGuiTableFlags_Borders))
                    {
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();

                        {                                                                           // sett figur count child window
                            ImGui::BeginChild("unit name", ImVec2(ImGui::GetContentRegionAvail().x * 0.64f, 21), false, window_flags);

                            ImGui::Text("Name -> ");
                            ImGui::SameLine();
                            ImGui::InputText("##", unitName[row], IM_ARRAYSIZE(unitName[row]));

                            ImGui::EndChild();
                        }

                        ImGui::SameLine();
                        int tootaltNrOfFigur = unitFigerCount[row] * unitCost[row];
                        ImGui::Text("cost figur's: %d", tootaltNrOfFigur);

                        {                                                                           // sett figur count child window
                            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                            ImGui::BeginChild("figu count", ImVec2(ImGui::GetContentRegionAvail().x * 0.48f, 21), false, window_flags);

                            ImGui::Text("nr of figurs: ");
                            ImGui::SameLine();
                            ImGui::InputInt("##", &unitFigerCount[row]);
                            ImGui::EndChild();
                        }

                        ImGui::SameLine();

                        {                                                                           // set Figur cost child window
                            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
                            ImGui::BeginChild("figur cost", ImVec2(ImGui::GetContentRegionAvail().x * 0.88f, 21), false, window_flags);

                            ImGui::Text("cost per figur: ");
                            ImGui::SameLine();
                            ImGui::InputInt("##", &unitCost[row]);

                            ImGui::EndChild();
                        }
                        ImGui::SameLine();


                        if (ImGui::BeginMenu("Edit -"))                                                // unit setings
                        {
                            ImGui::Checkbox("Show Note", &showNote[row]);
                            ImGui::InputInt("Nr of uppgrade", &uppgradeNrArray[row]);
                            ImGui::Text("Uppgrade's");
                            ImGui::InputInt("select uppgrade", &uppgradeSelected);
                            ImGui::InputInt("Uppgrade Cost", &setUppgradeCost);
                            {
                                ImGui::BeginChild("sett uppgarde name", ImVec2(ImGui::GetContentRegionAvail().x * 0.71f, 21), false);
                                ImGui::InputText("name", setUppgradeName, IM_ARRAYSIZE(setUppgradeName));
                                ImGui::EndChild();
                            }

                            if (ImGui::SmallButton("   !Sett name end pric!   "))
                            {
                                uppgradeCostArray[row][uppgradeSelected] = setUppgradeCost;
                                uppgradeNameArray[row][uppgradeSelected] = setUppgradeName;
                            };

                            ImGui::EndMenu();                                                      //sluter meny
                        }                                                                          // end of unit setings


                        float uppgradeWindowSize = uppgradeNrArray[row] * 21;
                        int lodeSpot = uppgradeNrArray[row];
                        for (short int i = 0; i < lodeSpot; i++)
                        {
                            {// sett figur count child window
                                std::string print_Uppgrade = "Name" + row + i;
                                ImGui::BeginChild(print_Uppgrade.c_str(), ImVec2(ImGui::GetContentRegionAvail().x * 0.25f, 24), false);

                                ImGui::InputText("name", setUppgradeName, IM_ARRAYSIZE(setUppgradeName));
                                ImGui::SameLine();
                                if (ImGui::SmallButton("Save"))
                                {
                                    uppgradeNameArray[row][i] = setUppgradeName;
                                }

                                ImGui::EndChild();
                            }                                                                       // sett figur count child window
                            ImGui::SameLine();                                                      //same line :D
                            {                                                                       // sett figur count child window
                                std::string print_Uppgrade = "Uppgarde" + row + i;

                                ImGui::BeginChild(print_Uppgrade.c_str(), ImVec2(ImGui::GetContentRegionAvail().x * 0.33f, 24), false);

                                ImGui::InputInt("cost", &uppgradeCostArray[row][i]);

                                ImGui::EndChild();
                            }// sett figur count child window
                        }

                        if (showNote[row])
                        {
                            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
                            flags = ImGuiInputTextFlags_CtrlEnterForNewLine;
                            ImGui::InputTextMultiline("##source", unitNotw[row], IM_ARRAYSIZE(unitNotw), ImVec2(-FLT_MIN, uppgradeWindowSize), flags);
                        }

                        ImGui::TableNextColumn();

                        int tootleUppgardeCost = 0;

                        for (int i = 0; i < 19; i++)
                        {
                            tootleUppgardeCost = tootleUppgardeCost + uppgradeCostArray[row][i];
                        }

                        int tootalCostOfUnit = unitFigerCount[row] * unitCost[row] + tootleUppgardeCost;
                        ImGui::Text("Tootal cost: %d", tootalCostOfUnit);

                        ImGui::EndTable();
                    }
                }
                ImGui::EndChild();//end child window
            }// liste side

            ImGui::SameLine();

            {//list menu edit

                ImGuiWindowFlags window_flags_Rsid = ImGuiWindowFlags_NoScrollbar;
                ImGui::BeginChild("righte side", ImVec2(ImGui::GetContentRegionAvail().x * 0.99f, winSiz.y), false, window_flags_Rsid);
                if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
                {
                    if (ImGui::BeginTabItem("Make List"))
                    {
                        ImGui::Text("Print Out:");
                        if (ImGui::Button("make file"))
                        {
                            make_list_file = true;
                        };
                        ImGui::SameLine();
                        if (ImGui::Button("Write to File"))
                        {
                            print_2_file = true;
                        };
                        ImGui::Text("how many Unit's?");
                        ImGui::InputInt("##", &UnitNr);

                        ImGui::Text("Uppgrade selecter:");

                        ImGui::InputInt("select unit", &unitSelected);

                        ImGui::InputInt("select uppgrade", &uppgradeSelected);

                        ImGui::InputInt("Uppgrade Cost", &setUppgradeCost);
                        {
                            ImGui::BeginChild("sett uppgarde name", ImVec2(ImGui::GetContentRegionAvail().x * 0.71f, 21), false);

                            ImGui::InputText("name", setUppgradeName, IM_ARRAYSIZE(setUppgradeName));

                            ImGui::EndChild();
                        }

                        if (ImGui::SmallButton("   !Sett name end pric!   "))
                        {
                            uppgradeCostArray[unitSelected][uppgradeSelected] = setUppgradeCost;
                            uppgradeNameArray[unitSelected][uppgradeSelected] = setUppgradeName;
                        };
                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("seting"))
                    {
                        if (ImGui::Button("Close App"))
                        {
                            ImGui_ImplOpenGL3_Shutdown();
                            ImGui_ImplGlfw_Shutdown();
                            ImGui::DestroyContext();

                            glfwDestroyWindow(window);
                            glfwTerminate();
                            return 0;
                        }
                        ImGui::SameLine();
                        ImGui::Checkbox("debug", &statestik);
                        ImGui::SameLine();
                        ImGui::Checkbox("Demo", &ImGuiDemo);

                        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
                        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                        ImGui::ShowFontSelector("font");
                        //ImGui::ShowStyleEditor();
                        //ImGui::ShowStyleSelector("styl");

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
                ImGui::EndChild();
            }// List menu edit

            ImGui::End();
        }
        //**

        /*  Render  */
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}