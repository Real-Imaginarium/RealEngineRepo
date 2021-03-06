#pragma once
#include "Types.h"

#include <stdint.h>
#include <string>
#include <map>
#include <vector>


// �������� ���� ������ ��� RegionsList
struct TestCell
{
    TestCell( size_t i = 0 )
        : field_1( 0 ), field_2( 0 ), field_3( 0 ), field_4( 0 ), field_5( 0 ), field_6( 0 ), field_7( i )
    {};
    uint32_t    field_1;
    uint32_t    field_2;
    float       field_3;
    uint16_t    field_4;
    char        field_5;
    char        field_6;
    size_t      field_7;

    TestCell& operator+=( size_t r_op ) {
        this->field_7 += r_op;
        return *this;
    }
    TestCell& operator-=( size_t r_op ) {
        this->field_7 -= r_op;
        return *this;
    }
    bool operator==( size_t r_op ) {
        return (this->field_7 == r_op);
    }
    bool operator!=( size_t r_op ) {
        return !(*this == r_op);
    }
};

struct Descriptor
{
    Descriptor( size_t i = 0 )
        : desc_handle( 0 ), index_in_heap( i )
    {};
    uint64_t desc_handle;
    uint64_t index_in_heap;

    Descriptor& operator+=( size_t r_op ) {
        this->index_in_heap += r_op;
        return *this;
    }
    Descriptor& operator-=( size_t r_op ) {
        this->index_in_heap -= r_op;
        return *this;
    }
    bool operator==( size_t r_op ) {
        return (this->index_in_heap == r_op);
    }
    bool operator!=( size_t r_op ) {
        return !(*this == r_op);
    }
};

/*����������������� ������ ���*/
//using CELL = TestCell;
using CELL = Descriptor;
//using CELL = uint8_t;


class Globals
{
public:
    // ���� � ������ ��� ��������� � ���������� ���������� ��� "Test_InsertionsComplex()"
    class InsertionsComplex
    {
    public:
        /* ����� ������� */
        enum InsertionPlace {
            Start_P1,
            P1_P2,
            P2_P3,
            P3_P4,
            P4_P5,
            P5_Finish,
            Regions_Count,
        };
        static const InsertionPlace InsertionPlaces[Regions_Count];


        /* ��������� ����� (���������� ��� P-List � S-List. ������ ���� - 1 RegionP ��� RegionS) */
        enum FieldState {
            L0_R0,
            L0_R1,
            L1_R0,
            L1_R1,
            FieldStates_Count
        };
        static const FieldState FieldStates[FieldStates_Count];


        /* ��� ������� � P-List */
        enum P_InsertionType
        {
            Start_P1_Adj_None,      // � ������, ���������
            Start_P1_Adj_R,         // � ������, �������
            P1_P2_Adj_None,         // ����� 1 � 2 ���������, ���������
            P1_P2_Adj_L,            // ����� 1 � 2 ���������, ������� � ����� (1)
            P1_P2_Adj_R,            // ����� 1 � 2 ���������, ������� � ������ (2)
            P1_P2_Adj_RL,           // ����� 1 � 2 ���������, ������� � ����� � ������ (1 � 2)
            P2_P3_Adj_None,         // ����� 2 � 3 ���������, ���������
            P2_P3_Adj_L,            // ����� 2 � 3 ���������, ������� � ����� (2)
            P2_P3_Adj_R,            // ����� 2 � 3 ���������, ������� � ������ (3)
            P2_P3_Adj_RL,           // ����� 2 � 3 ���������, ������� � ����� � ������ (2 � 3)
            P3_P4_Adj_None,         // ����� 3 � 4 ���������, ���������
            P3_P4_Adj_L,            // ����� 3 � 4 ���������, ������� � ����� (3)
            P3_P4_Adj_R,            // ����� 3 � 4 ���������, ������� � ������ (4)
            P3_P4_Adj_RL,           // ����� 3 � 4 ���������, ������� � ����� � ������ (3 � 4)
            P4_P5_Adj_None,         // ����� 4 � 5 ���������, ���������
            P4_P5_Adj_L,            // ����� 4 � 5 ���������, ������� � ����� (4)
            P4_P5_Adj_R,            // ����� 4 � 5 ���������, ������� � ������ (5)
            P4_P5_Adj_RL,           // ����� 4 � 5 ���������, ������� � ����� � ������ (4 � 5)
            P5_Finish_Adj_None,     // � �����, ���������
            P5_Finish_Adj_L,        // � �����, �������
            P_InsertionTypes_Count
        };
        static const P_InsertionType P_InsertionTypes[P_InsertionTypes_Count];


        /* ��� �������� � S-List (������� �� ���� ������� � P-List) */
        enum S_ActionType {
            IR,             // ������� ������
            IL,             // ������� �����
            DR_IR,          // �������� ������, ������� ������
            DR_IL,          // �������� ������, ������� �����
            DL_IR,          // �������� �����, ������� ������
            DL_IL,          // �������� �����, ������� �����
            DL_DL_IR,       // 2 �������� �����, ������� ������
            DL_DL_IL,       // 2 �������� �����, ������� �����
            DL_DR_IR,       // �������� ����� � ������, ������� ������
            DL_DR_IL,       // �������� ����� � ������, ������� �����
            DR_DL_IR,       // �������� ������ � �����, ������� ������
            DR_DL_IL,       // �������� ������ � �����, ������� �����
            DR_DR_IR,       // 2 �������� ������, ������� ������
            DR_DR_IL,       // 2 �������� ������, ������� �����
            S_ActionTypes_Count
        };
        static const S_ActionType S_ActionTypes[S_ActionTypes_Count];


        // �������� �������� ������� ������
        enum class Bounds {
            MEM_SIZE = 37,
            REG_1_START = 4,
            REG_2_START = 10,
            REG_3_START = 16,
            REG_4_START = 22,
            REG_5_START = 28,
        };
        // ������� ������� ������ ��� �������� ���������� 5 ������������� �������� ������ ������ (�������� 5 CELL), �������� ���������������� RegionsList.
        //
        //          [ ][ ][ ][ ][0][#][#][#][#][ ][1][#][#][#][#][ ][2][#][#][#][#][ ][3][#][#][#][#][ ][4][#][#][#][#][ ][ ][ ][ ]
        static CELL mem[(size_t)Bounds::MEM_SIZE];


        // ��������� �� ������ 5 ������������� �������� + ��������� �� ����� ������
        static CELL* const regPtrs[Regions_Count];


        // ����� �������� � �������������� ��������� P- � S-List � ��������� ���������
        static const std::tuple<std::string, ListState, ListState> P_States[FieldStates_Count][P_InsertionTypes_Count];

        static const std::tuple<std::string, ListState, ListState> S_States[FieldStates_Count][S_ActionTypes_Count];


        // ���������� ��� ����������� �������� � S-List.
        static S_ActionType SListActionDetermination( Side ins, Side del1, Side del2 );
    };

    // ���� � ������ ��� Test_ListsReorganise(); 
    class ReorganizeComplex
    {
    public:
        // ������� ������� ������
        static const size_t mem_size = 859;
        static CELL m[mem_size];

        // ������� ������� ������, ��� ������� � RegionsList � ����� ��� ������������� (������� �������� ��� ����������)
        static const size_t regs_count = 40;
        static RegionP<CELL> r[regs_count];

        // ���������, ������ ��������: �������� � �������������� ��������� (���������� ��� P-�-S-List), �������� � ��������������
        // ������� P-List (S-List ����������������� �� ���� � �����), �������. ��������� ����������.
        static const std::tuple<ListState, ListState, std::vector<RegionP<CELL>>, std::vector<RegionP<CELL>>, RegionP<CELL>> test_cases[66];

        // ������������������ ���������� ��� ������������ ������������� RegionsList. ������ ��������: �������� � �������������� ��������� (���������� ��� P-�-S-List),
        // ����� ���������������� ������� � �������� (true - �������, false - ������, ��. ���������) ��� ������������� RegionsList � �������������� �������.
        static const std::tuple<ListState, ListState, std::vector<std::tuple<RegionP<CELL>, bool>>, std::vector<RegionP<CELL>>> test_sequences[6];
    };
};