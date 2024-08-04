--自定义的协议解析

local this_plugin_info = {
    version = "0.1.0",
    description = "Wireshark plugin demo",
    author = "qianrui"
}

set_plugin_info(this_plugin_info)

--定义字段
local f_Version = ProtoField.uint8("myproto.version", "协议版本", base.DEC)
local f_Type = ProtoField.uint8("myproto.type", "类型", base.DEC)
local f_TotalLen = ProtoField.uint8("myproto.totalLen", "总长度", base.DEC)
local f_Reserved = ProtoField.uint8("myproto.reserved", "保留", base.DEC)

--定义协议
local p_myproto = Proto("myproto", "示例协议")

--添加字段
p_myproto.fields = {
    f_Version,
    f_Type,
    f_TotalLen,                 
    f_Reserved
}

local data_dis = Dissector.get("data")

--编写dissector
function p_myproto.dissector(buf, pkt, tree)
    pinfo.cols.protocol = p_myproto.name

    local subtree = tree:add(p_myproto, buf(0))
    subtree:add(f_Version, buf(0, 1))
    subtree:add(f_Type, buf(1, 1))
    subtree:add(f_TotalLen, buf(2, 2))
    subtree:add(f_Reserved, buf(4, 4))
    data_dis:call(buf(8):tvb(), pkt, tree)
end

--将12345端口识别为我们的协议
local udp_port_table = DissectorTable.get("udp.port")
udp_port_table:add(12345, p_myproto)
