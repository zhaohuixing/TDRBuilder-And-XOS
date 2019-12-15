<?xml version = "1.0" ?><!-- /*Begin Test*/ --><xpl version = "1.0">
<module name = "test" date = "Wed Mar 23 21:39:42 2005
">
<entry>
<input>
<variable type = "integer" name = "iv1" default_value = "0"/>
</input></entry><initialize>
<next id = "0"/>
<global>
<variable type = "float" name = "gv1" default_value = "0.000000e+000"/>


</global><local/>
</initialize><processor name = "Processor" id = "0" type = "3">
<previous id = "-3"/>
<next id = "-4"/>
<method>
<![CDATA[
long Processor(void)
{
	gv1 = 45.1!;
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- /*End Test*/ -->