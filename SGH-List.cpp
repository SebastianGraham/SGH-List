#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include "PrintFILE.h"

#include <iostream>
int main(void)
{
    GLFWwindow* window;


    if (!glfwInit())    /* Initialize the library */
        return -1;


    window = glfwCreateWindow(1680, 820, "SGH_List", NULL, NULL);   //Create a windowed mode window and its OpenGL context */
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);         /* Make the window's context current */
    glfwSwapInterval(1);                    // Enable vsync


    IMGUI_CHECKVERSION();                   /*  set up  Dear ImGui  */
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io; /*Get Computer IO*/



    ImGui::StyleColorsDark();               //style

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //window open velus
    bool        statestik = false, ImGuiDemo = false,
        make_list_file = false, print_2_file = false;
    ImVec4      clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

    //ARRAY FOR VER VERDI PER UPGRADE, STYRES AV I FRA FORLOOP
    std::string uppgradeNameArray[200][20];          //Valu for Upgrade array's                                   
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 20; j++) {
            uppgradeNameArray[i][j] = "";
        }
    };

    int     uppgradeCostArray[200][20];             //UNTAK UPPGARDE NR SOM HOLDER ANATALE UPGRADES 
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 20; j++) {
            uppgradeCostArray[i][j] = 0;
        }
    };

    int     uppgradeInnputArray[200][20];            //UNTAK UPPGARDE NR SOM HOLDER VILKEN UPPGARDE DU OPPDATERE
    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 20; j++) {
            uppgradeInnputArray[i][j] = 0;
        }
    };

    static char listName[32] = "";

    int         uppgradeCost = 0, uppgradeNr = 0, uppgradeNrArray[20] = {},
        unitFigerCount[200] = {}, UnitNr = 0, unitFigerCost[200] = {},
        tootleSum = 0;

    // sett upgrade velus
    int         uppgradeSelected = 0,
        unitSelected = 0,
        setUppgradeCost = 0;

    bool        showUnitNote[20] = { false },
        ShowUppgardeNote[200][20] = { {false} },
        uppgradeType[200][20] = { {false} };

    static char unitName[200][32] = { {} },
        setUppgradeName[32] = "",
        unitNote[200][255 * 6] = { {} },
        uppgradeNote[200][20][255 * 6] = { {} };


    while (!glfwWindowShouldClose(window))      /* MAIN LOOP */
    {

        glClear(GL_COLOR_BUFFER_BIT);           /* Render here */

        ImGui_ImplOpenGL3_NewFrame();           /* Nye Frame OpenGL3*/
        ImGui_ImplGlfw_NewFrame();              /* Nye Frame GLFW   */
        ImGui::NewFrame();                      /* Nye Frame ImGUI  */

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
            PrintFILE x;
            x.createFile(listName);
            make_list_file = false;
        }

        if (print_2_file)
        {
            PrintFILE x;
            x.writeList(listName, uppgradeNameArray, uppgradeCostArray,
                uppgradeNrArray, unitFigerCount, unitFigerCost, unitName, unitNote, UnitNr);
            print_2_file = false;
        }

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        {                                                                       // start på hoved vindu i ImGui
            ImGuiWindowFlags main_window_flags = 0;
            main_window_flags |= ImGuiWindowFlags_NoTitleBar;
            main_window_flags |= ImGuiWindowFlags_MenuBar;
            main_window_flags |= ImGuiWindowFlags_NoResize;
            main_window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            main_window_flags |= ImGuiWindowFlags_NoBackground;
            main_window_flags |= ImGuiWindowFlags_NoScrollbar;
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
                    ImGui::MenuItem("Save", NULL, &print_2_file);               // Uppdate List

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            {
                ImGui::BeginChild("List side", ImVec2(ImGui::GetContentRegionAvail().x * 0.65f, viewport->Size.y), false, NULL);
                {
                    ImGui::BeginChild("topPartL", ImVec2(ImGui::GetContentRegionAvail().x * 0.65f, 30), false, ImGuiWindowFlags_NoScrollbar);

                    ImGui::Text("List name:");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(350);
                    ImGui::InputText("##", listName, IM_ARRAYSIZE(listName));
                    ImGui::SameLine();
                    
                    ImGui::SeparatorText("## Top Part L");

                    ImGui::EndChild();
                }
                ImGui::SameLine();                                      //To make Top L & R to saty on same line
                {
                    ImGui::BeginChild("topPartR", ImVec2(ImGui::GetContentRegionAvail().x * 1.0f, 30), false, ImGuiWindowFlags_NoScrollbar);
                    ImGui::SameLine();
                    ImGui::Text("Unit's");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(90);
                    ImGui::InputInt("##", &UnitNr);
                    ImGui::SameLine();
                    ImGui::Text("|tootle List cost: %d", tootleSum);
                    ImGui::SameLine();

                    ImGui::SeparatorText("## Top Part R");

                    ImGui::EndChild();
                }
                ImGui::SeparatorText("## unit's");

                for (size_t Unit_Load = 0; Unit_Load < UnitNr; Unit_Load++)
                {
                    std::string Unit_ID = "unit ID" + Unit_Load + UnitNr;
                    
                    ImGui::PushID(Unit_Load);
                    ImGui::Text("                                 ");
                    ImGui::SameLine();
                    ImGui::PushItemWidth(350);
                    ImGui::InputText("## Unit name", unitName[Unit_Load], IM_ARRAYSIZE(unitName[Unit_Load]));
                    ImGui::SameLine();
                    if (ImGui::BeginMenu("- Edit -"))                                           // unit setings
                    {
                        ImGui::PushItemWidth(90);
                        ImGui::InputInt("Nr of uppgrade", &uppgradeNrArray[Unit_Load]);
                        ImGui::Checkbox("Show unit Note", &showUnitNote[Unit_Load]);

                        ImGui::EndMenu();                                                      //sluter meny
                    }

                    ImGui::PushItemWidth(90);
                    ImGui::InputInt("Nr of figurs", &unitFigerCount[Unit_Load]);
                    ImGui::SameLine();
                    ImGui::PushItemWidth(90);
                    ImGui::InputInt("cost", &unitFigerCost[Unit_Load]);

                    tootleSum = unitFigerCost[Unit_Load] * unitFigerCount[Unit_Load];

                    if (showUnitNote[Unit_Load])
                    { 
                        ImGui::SameLine();
                        ImGui::InputTextMultiline("## Unit Note", unitNote[Unit_Load], IM_ARRAYSIZE(unitNote[Unit_Load]), ImVec2(430,50));

                        ImGui::Text("All Model cost: %d", tootleSum);
                    }

                    if (!showUnitNote[Unit_Load])
                    {
                        ImGui::SameLine();
                        ImGui::Text("  |  All Model cost: %d", tootleSum);
                    }

                    for (size_t un_up = 0; un_up < uppgradeNrArray[Unit_Load]; un_up++)
                    {
                        ImGui::PushID(un_up);
                        {
                            ImGui::BeginChild("Child Windo", ImVec2(ImGui::GetContentRegionAvail().x * 0.40f, 55), true);

                            //
                            ImGui::PushItemWidth(320);
                            ImGui::Text("name : %s", uppgradeNameArray[Unit_Load][un_up].c_str());
                            
                            ImGui::SameLine();
                            ImGui::PushItemWidth(90);
                            ImGui::InputInt("##Uppgrade cost", &uppgradeCostArray[Unit_Load][un_up]);
                            ImGui::PushItemWidth(410);


                            if (ImGui::BeginMenu("Uppgrade menu"))
                            {
                                ImGui::PushID(un_up + Unit_Load);

                                ImGui::InputText("##Uppgrade Name", setUppgradeName, IM_ARRAYSIZE(setUppgradeName));
                                ImGui::SameLine();

                                if (ImGui::ArrowButton) 
                                {
                                    uppgradeNameArray[Unit_Load][un_up] = setUppgradeCost;
                                }

                                ImGui::Checkbox("uppgarde type", &uppgradeType[Unit_Load][un_up]);
                                ImGui::SameLine;
                                ImGui::Checkbox("uppgarde note", &ShowUppgardeNote[Unit_Load][un_up]);

                                
                                ImGui::PopID();
                                ImGui::EndMenu();
                            }
                            //

                            ImGui::EndChild();
                        }
                        ImGui::PopID();
                    }

                    ImGui::SeparatorText("## unit end");
                    ImGui::PopID();
                }

                ImGui::EndChild();
            }                   // List side

            ImGui::SameLine(); /*================================================>>  User input L <>  Menu R*/

            {
                ImGui::BeginChild("List Menu side", ImVec2(ImGui::GetContentRegionAvail().x * 1.0f, viewport->Size.y), false, NULL);
                
                if (ImGui::BeginTabBar("menu Tab Bar", 0))
                {
                    if (ImGui::BeginTabItem(" prewi "))
                    {

                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem(" queek edit "))
                    {
                        
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem(" setings "))
                    {
                            static const char* item_names[] = { "Item One", "Item Two", "Item Three", "Item Four", "Item Five" };
                            for (int n = 0; n < IM_ARRAYSIZE(item_names); n++)
                            {
                                const char* item = item_names[n];
                                ImGui::Selectable(item);

                                if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
                                {
                                    int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
                                    if (n_next >= 0 && n_next < IM_ARRAYSIZE(item_names))
                                    {
                                        item_names[n] = item_names[n_next];
                                        item_names[n_next] = item;
                                        ImGui::ResetMouseDragDelta();
                                    }
                                }
                            }

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
                ImGui::EndChild();
            }

            ImGui::End();// End main prog win
        }

           ImGui::Render();                           /*  Render  */
           ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
           glfwSwapBuffers(window);/* Swap front and back buffers */
           glfwPollEvents();       /* Poll for and process events */

    }//wheal

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    
}//main