#include "Player.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"

Player::Player():ShooterObject(){

}

void Player::load(std::unique_ptr<LoaderParams> const& params){
    ShooterObject::load(params);

    renderOffset.spriteOffsetX = params->getSpriteOffsetX();
    renderOffset.spriteOffsetY = params->getSpriteOffsetY();
    
    m_velocity = ivec2(0,0);

    m_collision.x += m_position.x;
    m_collision.y += m_position.y;
}

void Player::draw(){
    auto textureManager = TextureManager::Instance();
    auto renderer = Game::Instance()->getRenderer();

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(m_playerFace==RIGHT){
        flip = SDL_FLIP_HORIZONTAL;
    }
    textureManager->drawFrame(m_textureID,this->m_position.x,this->m_position.y,m_width,m_height,m_currentRow,m_currentFrame,renderer,m_angle,m_alpha,renderOffset,flip);

    SDL_SetRenderDrawColor(renderer, 15, 255, 15, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer,&m_collision);
}

void Player::update(){
    // if the level is complete then fly off the screen
    auto game = Game::Instance();
    if(game->getLevelComplete()){
        if(m_position.x >= game->getGameWidth()){
            game->setCurrentLevel(game->getCurrentLevel() + 1);
        }else{
            m_velocity.x = 0;
            m_velocity.y = 3;
            ShooterObject::update();
            handleAnimation();
        }
    }else{
        // if the player is not doing its death animation then update it normally
        if(!m_dying){
            // reset velocity
            m_velocity = {0,0};
            // get input
            handleInput();
            // do normal position += velocity update
            ShooterObject::update();
            // update the animation
            handleAnimation();
        }else {
            // if the player is doing the death animation
            m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
            // if the death animation has completed
            if(m_dyingCounter == m_dyingTime){
                // ressurect the player
                ressurect();
            }
            m_dyingCounter++;
        }
    }

    if(m_velocity.x>0){
        m_playerFace = RIGHT;
    }
    if(m_velocity.x<0){
        m_playerFace = LEFT;
    }
}

void Player::clean(){
    ShooterObject::clean();
}

void Player::handleInput(){
    auto ih = InputHandler::Instance();
    if(ih->joysticksInitialised()){
        vec2 leftLR = ih->axis(0,1);
        vec2 leftUD = ih->axis(0,2);

        if(leftLR.x!=0){
            m_velocity.x = leftLR.x;
        }

        if(leftLR.y!=0){
            m_velocity.y = leftLR.y;
        }

        if(leftUD.x!=0){
            m_velocity.x = leftUD.x;
        }

        if(leftUD.y!=0){
            m_velocity.y = leftUD.y;
        }

        //button Y of the XOBX 360 Controller
        if(ih->getButtonState(0,3)){
            m_velocity.x = 1;
        }
    }

    if(ih->getMouseButtonState(MIDDLE)){
        m_velocity.x = 1;
    }

    // m_velocity = (ih->getMousePosition()-m_position)/100;
    if(ih->isKeyDown(SDL_SCANCODE_RIGHT)){
        m_velocity.x = 2;
    }
    if(ih->isKeyDown(SDL_SCANCODE_LEFT)){
        m_velocity.x = -2;
    }
    if(ih->isKeyDown(SDL_SCANCODE_UP)){
        m_velocity.y = -2;
    }
    if(ih->isKeyDown(SDL_SCANCODE_DOWN)){
        m_velocity.y = 2;
    }
}

void Player::handleAnimation(){
    if(m_invulnerable){
        if(m_invulnerableCounter==m_invulnerableTime){
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }else{
            m_alpha = m_alpha==255?0:255;
        }

        m_invulnerableCounter++;
    }

    if(!m_dead){
        
    }

    m_currentFrame = int((SDL_GetTicks()/100)%m_numFrames);
}

void Player::ressurect(){
    Game::Instance()->setPlayerLives(Game::Instance()->getPlayerLives()-1);

    m_position.x = 10;
    m_position.y = 200;
    m_dying = false;
    m_textureID = "player";
    m_currentFrame = 1;
    m_numFrames = 4;
    m_width = 120;
    m_height = 40;
    m_dyingCounter = 0;
    m_invulnerable = true;
}