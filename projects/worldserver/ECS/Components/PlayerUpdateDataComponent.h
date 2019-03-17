/*
    MIT License

    Copyright (c) 2018-2019 NovusCore

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#pragma once
#include <NovusTypes.h>
#include <vector>

#include <Networking/ByteBuffer.h>
#include "../NovusEnums.h"
#include "../Connections/NovusConnection.h"

struct PositionUpdateData
{
    u16 opcode;
    u32 movementFlags;
    u16 movementFlagsExtra;
    u32 gameTime;
    f32 x;
    f32 y;
    f32 z;
    f32 orientation;
    u32 fallTime;
};

struct PlayerUpdateDataComponent
{
    PlayerUpdateDataComponent() : changesMask(PLAYER_END), playerFields(PLAYER_END * 4) { }

    void SetGuidValue(u16 index, u64 value)
    {
        playerFields.WriteAt<u64>(value, index * 4);
        changesMask.SetBit(index);
        changesMask.SetBit(index + 1);
    }
    template <typename T>
    void SetFieldValue(u16 index, T value, u8 offset = 0)
    {
        playerFields.WriteAt<T>(value, (index * 4) + offset);
        changesMask.SetBit(index);
    }
    template <typename T>
    T GetFieldValue(u16 index, u8 offset = 0)
    {
        return playerFields.ReadAt<T>((index * 4) + offset);
    }
    void ResetFields()
    {
        playerFields.Clean();
        playerFields.Resize(PLAYER_END * 4);
        changesMask.Reset();
    }

    UpdateMask<1344> changesMask;
    Common::ByteBuffer playerFields;
    std::vector<u32> visibleGuids;
    std::vector<PositionUpdateData> positionUpdateData;
};