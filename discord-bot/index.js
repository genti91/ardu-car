const { Client, GatewayIntentBits, Partials, ActionRowBuilder, ButtonBuilder, ButtonStyle, EmbedBuilder } = require('discord.js');
var net = require('net');
const config = require('./config.js');

const express = require('express')
const app = express()
const port = 5001


const HOST = '192.168.0.19';
const PORT = 9000;

var socket = new net.Socket();
socket.connect(PORT, HOST);
socket.on('connect', () => {
    console.log('Connected');
});
socket.on('data', (data) => {
    console.log(`${data}`);
});

var light = 'off'

const bot = new Client({ 
    intents: [
        GatewayIntentBits.Guilds, 
        GatewayIntentBits.GuildMessages, 
        GatewayIntentBits.MessageContent, 
        GatewayIntentBits.GuildMembers, 
        GatewayIntentBits.GuildVoiceStates
    ], 
    partials: [Partials.Channel] 
});


app.get('/', (req, res) => {
    res.send('Finished!')
    console.log("Finished!")
    
})
app.listen(port, () => {
    console.log(`Express app on port ${port}`)
})


bot.on('ready', () => {
    console.log('bot is working');
});

bot.on('messageCreate', (msg) => {

    if (msg.content.startsWith("-w") || msg.content.startsWith("-s") || msg.content.startsWith("-a") || msg.content.startsWith("-d")){
        if (!isNaN(msg.content.substring(msg.content.indexOf(" ") + 1))) {
            let number = parseInt(msg.content.substring(msg.content.indexOf(" ") + 1))
            if (number > 0 && number <= 5000) {
                socket.write(msg.content)
            }
        }
        msg.delete()
    }

    if(msg.content === '!button'){
        const row1 = new ActionRowBuilder()
        .addComponents(
            new ButtonBuilder()
            .setCustomId('song')
            .setLabel('🎶')
            .setStyle(ButtonStyle.Secondary),
        )
        .addComponents(
            new ButtonBuilder()
            .setCustomId('Up')
            .setLabel('⬆️')
            .setStyle(ButtonStyle.Primary),
        )
        .addComponents(
            new ButtonBuilder()
            .setCustomId('on')
            .setLabel('🔦')
            .setStyle(ButtonStyle.Secondary),
        )

        const row2 = new ActionRowBuilder()
        .addComponents(
            new ButtonBuilder()
            .setCustomId('Left')
            .setLabel('⬅️')
            .setStyle(ButtonStyle.Primary),
        )
        .addComponents(
            new ButtonBuilder()
            .setCustomId('song_stop')
            .setLabel('-')
            .setStyle(ButtonStyle.Secondary),
        )
        .addComponents(
            new ButtonBuilder()
            .setCustomId('Right')
            .setLabel('➡️')
            .setStyle(ButtonStyle.Primary),
        )

        const row3 = new ActionRowBuilder()
        .addComponents(
            new ButtonBuilder()
            .setCustomId('open')
            .setLabel('close')
            .setStyle(ButtonStyle.Secondary),
        )
        .addComponents(
            new ButtonBuilder()
            .setCustomId('Down')
            .setLabel('⬇️')
            .setStyle(ButtonStyle.Primary),
        )
        .addComponents(
            new ButtonBuilder()
            .setCustomId('close')
            .setLabel('open')
            .setStyle(ButtonStyle.Secondary),
        )

        const embed = new EmbedBuilder()
        .setColor("Blue")
        .setDescription(`${msg.author.tag}'s button!`)
        
        const embed2 = new EmbedBuilder()
        .setColor("Blue")
        .setDescription("The botton was pressed")

        msg.channel.send({ embeds: [], components: [row1, row2, row3]});

        const collector = msg.channel.createMessageComponentCollector();

        collector.on('collect', async i => {
            
            if (i.customId === 'on') {
                if (light === 'off') {
                    socket.write('on')
                    light = 'on'
                }else{
                    socket.write('off')
                    light = 'off'
                }

            }else{
                socket.write(i.customId)
            }
            
            await i.update({ embeds: [], components: [row1, row2, row3]})
        });
    }
});


bot.login(config.bot_key);


